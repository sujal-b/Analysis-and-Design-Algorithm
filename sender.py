import socket
import time
import random
import threading

# --- CONFIGURATION ---
[cite_start]TOTAL_FRAMES = 10 # [cite: 110]
[cite_start]WINDOW_SIZE = 4   # [cite: 111]
[cite_start]LOSS_PROBABILITY = 0.2 # [cite: 113]
TIMEOUT_DURATION = 3.0 # Seconds before resending

# Shared Variables (Protected by Lock)
[cite_start]base = 0      # [cite: 157]
lock = threading.Lock()
timer_start = time.time()

def ack_listener(conn):
    """Running in a separate thread to listen for ACKs constantly"""
    global base, timer_start
    while True:
        try:
            response = conn.recv(1024).decode()
            if not response:
                break
                
            [cite_start]if response.startswith("ACK"): # [cite: 130]
                ack_num = int(response.replace("ACK", ""))
                print(f"   [ACK-Thread] Received ACK for Frame {ack_num}")
                
                with lock:
                    # In GBN, Ack N means everything up to N is safe.
                    # We move base to ack_num + 1
                    if ack_num >= base:
                        base = ack_num + 1
                        timer_start = time.time() # Reset timer on valid ACK
                        
        except:
            break

def sender_program():
    global base, timer_start
    
    # Create Socket and Connect
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    [cite_start]s.connect(('127.0.0.1', 9999)) # [cite: 148]
    
    print(f"--- Sender Started (Go-Back-N Mode) ---\n")

    # Start the listener thread
    [cite_start]threading.Thread(target=ack_listener, args=(s,), daemon=True).start() # [cite: 154]

    [cite_start]next_seq_num = 0 # [cite: 158]

    [cite_start]while base < TOTAL_FRAMES: # [cite: 161]
        
        with lock:
            current_base = base
        
        # 1. SENDING LOGIC: If window is not full
        if next_seq_num < current_base + WINDOW_SIZE and next_seq_num < TOTAL_FRAMES:
            
            # Simulate Packet Loss
            [cite_start]if random.random() > LOSS_PROBABILITY: # [cite: 171]
                print(f"[Sender] Sending Frame {next_seq_num}")
                s.send(str(next_seq_num).encode())
            else:
                print(f"[Sender] -- SIMULATED LOSS -- Frame {next_seq_num} dropped.")
            
            next_seq_num += 1
            time.sleep(1) # Slow down so you can read the output
            
        # 2. TIMEOUT LOGIC: If we are stuck
        elif time.time() - timer_start > TIMEOUT_DURATION:
            print(f"\n[Sender] !! TIMEOUT !! No ACK for {current_base}. Resending Window from {current_base}...\n")
            
            with lock:
                # GO BACK N: Reset next_seq_num to the base
                next_seq_num = base 
                timer_start = time.time() # Reset timer
                
        else:
            # Window is full, waiting for ACK...
            pass

    # End of Transmission
    [cite_start]s.send(b"END") # [cite: 204]
    print("\n--- All Frames Acknowledged. Transfer Complete. ---")
    s.close()

if __name__ == "__main__":
    sender_program()