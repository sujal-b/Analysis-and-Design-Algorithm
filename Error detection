#include <stdio.h>

int main() {
    int data[8], received[8], i;
    int c1, c2, c3, c;

    printf("--- SENDER SIDE ---\n");
    printf("Enter 4 data bits (D3, D5, D6, D7) separated by space: ");
    // Store data in positions that are NOT powers of 2
    scanf("%d %d %d %d", &data[3], &data[5], &data[6], &data[7]);

    // Calculation (Standard P1, P2, P4 positions)
    // P1 (Pos 1) checks 1, 3, 5, 7
    data[1] = data[3] ^ data[5] ^ data[7];
    
    // P2 (Pos 2) checks 2, 3, 6, 7
    data[2] = data[3] ^ data[6] ^ data[7];
    
    // P4 (Pos 4) checks 4, 5, 6, 7
    data[4] = data[5] ^ data[6] ^ data[7];

    printf("Encoded Data (P1 P2 D3 P4 D5 D6 D7): ");
    for(i = 1; i <= 7; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    // --- RECEIVER SIDE ---
    printf("\n--- RECEIVER SIDE ---\n");
    printf("Enter received 7 bits one by one: ");
    for(i = 1; i <= 7; i++) {
        scanf("%d", &received[i]);
    }

    c1 = received[1] ^ received[3] ^ received[5] ^ received[7];
    c2 = received[2] ^ received[3] ^ received[6] ^ received[7];
    c3 = received[4] ^ received[5] ^ received[6] ^ received[7];

    int error_pos = (c3 * 4) + (c2 * 2) + (c1 * 1);

    if(error_pos == 0) {
        printf("\nResult: No error detected.\n");
    } else {
        printf("\nResult: Error detected at Position %d\n", error_pos);

        received[error_pos] = !received[error_pos]; 
        
        printf("Corrected Data: ");
        for(i = 1; i <= 7; i++) {
            printf("%d ", received[i]);
        }
        printf("\n");
    }

    return 0;
}
