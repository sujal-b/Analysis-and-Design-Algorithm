#include <stdio.h>

int main() {
    int total_frames, lost_frame, i, choice;

    printf("Enter Total Number of Frames to Send: ");
    scanf("%d", &total_frames);

    // We simulate that a specific frame is lost to see how the code reacts
    printf("Enter the Frame Number to simulate as LOST (e.g., 2): ");
    scanf("%d", &lost_frame);

    printf("\nChoose Protocol:\n");
    printf("1. Go-Back-N ARQ\n");
    printf("2. Selective Repeat ARQ\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    printf("\n------------------------------------------------\n");

    // LOGIC FOR GO-BACK-N
    if (choice == 1) {
        printf("Simulating Go-Back-N Protocol:\n");
        
        // Step 1: Send frames up to the lost one
        for (i = 1; i <= total_frames; i++) {
            if (i == lost_frame) {
                printf("Sent Frame %d -> LOST (No ACK Received)\n", i);
                printf("!! Timer Expired for Frame %d !!\n", i);
                
                // CRITICAL GBN LOGIC:
                // Go back to the lost frame and resend EVERYTHING from there [cite: 139]
                printf("...Go Back and Resend Frame %d and all subsequent frames...\n", i);
                
                // Restart loop from the lost frame
                for (int j = i; j <= total_frames; j++) {
                    printf("Resent Frame %d -> ACK Received\n", j);
                }
                break; // Stop the outer loop because we finished sending in the inner loop
            } else {
                printf("Sent Frame %d -> ACK Received\n", i);
            }
        }
    }

    // LOGIC FOR SELECTIVE REPEAT
    else if (choice == 2) {
        printf("Simulating Selective Repeat Protocol:\n");
        
        // Step 1: Send all frames. If one is lost, keep going.
        for (i = 1; i <= total_frames; i++) {
            if (i == lost_frame) {
                printf("Sent Frame %d -> LOST (No ACK, NAK Sent)\n", i);
                // CRITICAL SR LOGIC: 
                // Don't stop. Continue sending the rest [cite: 140, 142]
            } else {
                printf("Sent Frame %d -> ACK Received\n", i);
            }
        }

        // Step 2: Resend ONLY the specific lost frame
        printf("\n...Selective Repeat Logic Triggered...\n");
        printf("Resending ONLY the lost Frame %d -> ACK Received\n", lost_frame);
    } 
    else {
        printf("Invalid Choice.\n");
    }

    return 0;
}
