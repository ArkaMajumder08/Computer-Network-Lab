#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4000
#define CLIENT_IP "127.0.0.1"
#define CLIENT_PORT 4001

int main() {
    struct sockaddr_in server = {0}, client = {0};
    int sn, slen = sizeof(server);
    char str[512];

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(CLIENT_IP);
    client.sin_port = htons(CLIENT_PORT);

    // Create UDP socket
    sn = socket(AF_INET, SOCK_DGRAM, 0);

    // Optional: bind client (to match your structure)
    bind(sn, (struct sockaddr *)&client, sizeof(client));

    printf("UDP client ready...\n");

    do {
        printf("Enter Something : ");
        fgets(str, sizeof(str), stdin);

        // Send to server
        sendto(sn, str, strlen(str) + 1, 0,
               (struct sockaddr *)&server, slen);

        // Receive from server
        recvfrom(sn, str, 512, 0,
                 (struct sockaddr *)&server, &slen);

        printf("Echoed : %s\n", str);

    } while (strncmp(str, "end", 3) != 0);

    close(sn);
    return 0;
}
