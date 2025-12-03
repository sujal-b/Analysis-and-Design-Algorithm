import socket
import time
import random

# --- CONFIGURATION (Must match Sender) ---
[cite_start]TOTAL_FRAMES = 10  # [cite: 110]
[cite_start]LOSS_PROBABILITY = 0.2 # [cite: 113]

def receiver_program():
    # Setup Server Socket
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    [cite_start]s.bind(('127.0.0.1', 9999)) # [cite: 148]
    s.listen(1)
    
    print(f"--- Receiver Started (Waiting for Connection) ---\n")
    conn, addr = s.accept()
    print(f"[Receiver] Connected to {addr}")

    [cite_start]expected_frame = 0 # [cite: 255]

    while True:
        try:
            # Receive data
            data = conn.recv(1024).decode()
            
            if not data:
                break
            
            # Check for End of Transmission
            [cite_start]if data == "END": # [cite: 139]
                print("\n[Receiver] 'END' received. Closing connection.")
                break

            # Simulate network delay for visibility
            time.sleep(0.5)

            # Parse the frame number
            # We use try/except because sometimes multiple numbers arrive at once (e.g. "12")
            try:
                frame = int(data) 
            except ValueError:
                continue

            # --- Go-Back-N Logic ---
            # If the frame matches what we are expecting
            [cite_start]if frame == expected_frame: # [cite: 301]
                # Simulate Random Loss of Acknowledgement? (Optional, but usually Receiver reliably ACKs)
                print(f"[Receiver] Frame {frame} Accepted. Sending ACK {frame}...")
                [cite_start]conn.send(f"ACK{frame}".encode()) # [cite: 302]
                expected_frame += 1
            else:
                # If frame is NOT what we expected (Out of Order)
                [cite_start]print(f"[Receiver] DISCARDED Frame {frame} (Expected {expected_frame})") # [cite: 305]

        except ConnectionResetError:
            break

    conn.close()
    s.close()

if __name__ == "__main__":
    receiver_program()