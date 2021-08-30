#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(void) {
    int sockfd, clientfd;
    struct sockaddr_in server;
    struct sockaddr_storage client;
    socklen_t client_size = sizeof client;
    int bytes_sent;
    char msg[] = "Hello world!";

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("failed to create socket\n");
        return -1;
    }

    // set server address struct
    memset(&server, 0, sizeof server);
    server.sin_family = AF_INET;
    server.sin_port = htons(59090);
    server.sin_addr.s_addr = INADDR_ANY;

    // bind
    if (bind(sockfd, (struct sockaddr *)&server, sizeof server) != 0) {
        printf("failed to bind\n");
        close(sockfd);
        return -1;
    }

    // listen for connections
    if (listen(sockfd, 5) != 0) {
        printf("failed to listen\n");
        close(sockfd);
        return -1;
    }
    
    printf("listening...\n");

    
    clientfd = accept(sockfd, (struct sockaddr *)&client, &client_size);

    printf("connected!\n");
        
    bytes_sent = send(clientfd, msg, sizeof msg, 0);
    printf("sent %d bytes\n", bytes_sent);
    
    close(sockfd);
    close(clientfd);
    
    return 0;
}
