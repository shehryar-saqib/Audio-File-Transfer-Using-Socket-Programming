#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 9999
#define SIZE 1024

void send_file(FILE* fp, int sockfd) {
    char buffer[SIZE];
    while (1) {
        size_t num_read = fread(buffer, 1, SIZE, fp);
        if (num_read == 0) {
            break;
        }

        int n = write(sockfd, buffer, num_read);
        if (n < 0) {
            perror("[-]Error Writing to Socket\n");
            exit(EXIT_FAILURE);
        }
        else if (n == 0) {
            break;
        }

    }
}

int main(int argc, char const *argv[]) {

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[SIZE] = {0};


    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("[-]Socket Creation Failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("[-]Error in setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    // address.sin_addr.s_addr = inet_addr("111.68.97.205");
    address.sin_port = htons(PORT);


    if ( bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0 ) {
        perror("[-]Binding Error");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("[-]Error Listening");
        exit(EXIT_FAILURE);
    }

    
    while (1) {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        printf("Connected to Client: %s over Port: %d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
        
        FILE* fp = fopen("audioFile.mp3", "rb");
        if (fp == NULL) {
            perror("[-]Error in reading file\n");
            exit(EXIT_FAILURE);
        }

        send_file(fp, new_socket);
        printf("File Sent Successfully to Client: %s\n\n", inet_ntoa(address.sin_addr));
        close(new_socket);
        
    }
    
    
    close(server_fd);

    return 0;
}