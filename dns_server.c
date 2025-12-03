#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

// Simple structure to mimic the Python Dictionary
struct DNSRecord {
    char key[100];
    char value[100];
};

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr, cliaddr;
    
    // Create socket file descriptor (IPv4, UDP)
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    // Configure server address
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY; // Localhost
    servaddr.sin_port = htons(PORT);
    
    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Define the DNS Mapping (Static Data)
    struct DNSRecord dns_table[] = {
        {"www.google.com", "142.250.190.68"},
        {"www.yahoo.com", "98.137.11.163"},
        {"www.dypitpune.edu.in", "192.168.1.100"},
        {"192.168.1.100", "www.dypitpune.edu.in"},
        {"142.250.190.68", "www.google.com"}
    };
    int table_size = 5;

    printf("DNS Server started... waiting for queries\n");

    socklen_t len;
    int n;

    while (1) {
        len = sizeof(cliaddr);
        
        // Receive data from client
        n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, 0, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0'; // Null-terminate the string
        
        printf("Received query: %s\n", buffer);
        
        // Resolve Query (Linear search through the array)
        char *response = "No record found";
        
        for (int i = 0; i < table_size; i++) {
            if (strcmp(buffer, dns_table[i].key) == 0) {
                response = dns_table[i].value;
                break;
            }
        }
        
        // Send response back to client
        sendto(sockfd, (const char *)response, strlen(response), 0, (const struct sockaddr *)&cliaddr, len);
        printf("Sent response: %s\n\n", response);
    }
    
    return 0;
}