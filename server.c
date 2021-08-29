#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(void) {
    int sockfd, clientfd;
    struct sockaddr_in server;
    struct sockaddr_storage client;
    socklen_t client_size;
    char msg[] = "Socket programming fucking blows!!!\n";

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
    
    if (bind(sockfd, (struct sockaddr *)&server, sizeof server) != 0) {
        printf("failed to bind\n");
        close(sockfd);
        return -1;
    }

    if (listen(sockfd, 5) != 0) {
        printf("failed to listen\n");
        close(sockfd);
        return -1;
    }
    
    printf("listening...\n");

    client_size = sizeof client;
    clientfd = accept(sockfd, (struct sockaddr *)&client, &client_size);

    printf("connected!\n");
        
    send(clientfd, msg, sizeof msg, 0);
    
    close(sockfd);
    close(clientfd);
    
    return 0;
}
