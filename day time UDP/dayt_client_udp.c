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
    int sd, slen = sizeof(server);
    char msg1[1024], msg2[1024];

    bzero((char *)&client, sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_PORT);
    client.sin_addr.s_addr = inet_addr(CLIENT_IP);

    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Create UDP socket
    sd = socket(AF_INET, SOCK_DGRAM, 0);

    // Optional bind (kept for similarity)
    bind(sd, (struct sockaddr *)&client, sizeof(client));

    do
    {
        printf("Enter a string to send to server : ");
        scanf("%s", msg1);

        // Send to server
        sendto(sd, msg1, strlen(msg1) + 1, 0,
               (struct sockaddr *)&server, slen);

        memset(msg2, 0x0, sizeof(msg2));

        // Receive from server
        recvfrom(sd, msg2, sizeof(msg2), 0,
                 (struct sockaddr *)&server, &slen);

        printf("Received : %s\n", msg2);

    } while (strcmp(msg1, "stop"));

    return 0;
}
