#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    char query[BUFFER_SIZE];
    struct sockaddr_in servaddr;
    
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    int n;
    socklen_t len;
    
    while (1) {
        printf("\nEnter Hostname or IP (or 'exit' to quit): ");
        
        if (fgets(query, sizeof(query), stdin) == NULL) break;
        
        query[strcspn(query, "\n")] = 0;
        
        if (strcmp(query, "exit") == 0) {
            break;
        }
        
        if (strlen(query) == 0) {
            continue;
        }

        sendto(sockfd, (const char *)query, strlen(query), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        
        len = sizeof(servaddr);
        n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, 0, (struct sockaddr *)&servaddr, &len);
        buffer[n] = '\0';
        
        printf("Resolved Address: %s\n", buffer);
    }
    
    close(sockfd);
    return 0;

}

