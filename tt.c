#include <stdio.h>

int main(){

    int data[8],received[8],c1,c2,c3;

    printf("Enter 4 data bits (0 or 1): \n");
    scanf("%d %d %d %d",&data[3],&data[5],&data[6],&data[7]);

    data[1] = data[3] ^ data[5] ^ data[7];
    data[2] = data[3] ^ data[6] ^ data[7];
    data[4] = data[5] ^ data[6] ^ data[7];

    printf("Encoded Data: ");
    for(int i=1;i<=7;i++){
        printf("%d ",data[i]);
    }

    printf("\n");
    printf("Enter received data bits: ");
    for(int i=1;i<=7;i++){
        scanf("%d",&received[i]);
    }

    printf("\n.....Decoding the Data.....");
    c1 = received[1] ^ received[3] ^ received[5] ^ received[7];
    c2 = received[2] ^ received[3] ^ received[6] ^ received[7];
    c3 = received[4] ^ received[5] ^ received[6] ^  received[7];

    int error_pos = (c1 * 1) + (c2 * 2) + (c3 * 4);

    if(error_pos == 0){
        printf("\nNo error Detected");
    }else{
        printf("\nError in position %d",error_pos);
        received[error_pos] = !received[error_pos];

        printf("\nCorrected Data: ");
        for(int j=1;j<=7;j++){
            printf("%d ",received[j]);
        }
    }
    return 0 ;
}