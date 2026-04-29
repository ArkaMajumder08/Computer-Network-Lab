#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define CLIENT_PORT 1024
#define SERVER_PORT 1025
#define CLIENT_IP "127.0.0.1"
#define SERVER_IP "127.0.0.1"
int main()
{
    struct sockaddr_in server, client;
    int sd;
    char msg1[1024], msg2[1024];
    bzero((char *)&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_PORT);
    client.sin_addr.s_addr = inet_addr(CLIENT_IP);

    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    sd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sd, (struct sockaddr *)&client, sizeof(client));
    connect(sd, (struct sockaddr *)&server, sizeof(server));
    do
    {
        printf("Enter a string to send to server : ");
        scanf("%s", msg1);
        send(sd, msg1, strlen(msg1) + 1, 0);
        memset(msg2, 0x0, sizeof(msg2));
        recv(sd, msg2, sizeof(msg2), 0);
        printf("Received : %s\n", msg2);

    } while (strcmp(msg1, "stop"));
    return 0;
}
