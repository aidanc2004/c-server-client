#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(void) {
    int sockfd;
    struct sockaddr_in server;
    char msg[13];

    // create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "failed to create socket\n");
        return -1;
    }

    // set server address struct
    memset(&server, 0, sizeof server);
    server.sin_family = AF_INET;
    server.sin_port = htons(59090);
    server.sin_addr.s_addr = INADDR_ANY;

    if ((connect(sockfd, (struct sockaddr *)&server, sizeof server)) != 0) {
        fprintf(stderr, "failed to connect\n");
        return -1;
    }

    recv(sockfd, msg, 13, 0);

    printf("recieved: %s\n", msg);

    close(sockfd);

    return 0;
}
