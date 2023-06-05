#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 9999
#define SIZE 1024

void write_file(int sockfd) {
    int n;
    FILE* fp;
    const char* filename = "recvAudio.mp3";
    char buffer[SIZE];

    fp = fopen(filename, "wb");
    while (1) {
        int n = read(sockfd, buffer, SIZE);
        if (n < 0) {
            perror("[-]Error Reading From Socket\n");
        }
        else if (n == 0) {
            break;
        }

        fwrite(buffer, 1, n, fp);
    }

    return;
}

int main(int argc, char const *argv[]) {

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[SIZE] = {0};
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("[-]Error Creating Socket");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid Address / Address not supported\n");
        return -1;
    }

    if ( connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 ) {
        printf("[-]Connection Failed");
        return -1;
    }

    write_file(sock);
    printf("File Received From Server.\n");
    printf("Closing Connection...\n");
    close(sock);

    return 0;
}