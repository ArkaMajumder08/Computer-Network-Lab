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

int main() {
    struct sockaddr_in server = {0}, client = {0};
    int sn, clen = sizeof(client);
    char str[512];

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    // Create UDP socket
    sn = socket(AF_INET, SOCK_DGRAM, 0);

    bind(sn, (struct sockaddr *)&server, sizeof(server));

    printf("UDP Echo server is listening...........\n");

    while (1) {
        printf("Waiting...\n");

        memset(str, 0x0, 512);

        // Receive from client
        recvfrom(sn, str, 512, 0,
                 (struct sockaddr *)&client, &clen);

        printf("Received : %s", str);

        // Send back (echo)
        sendto(sn, str, strlen(str) + 1, 0,
               (struct sockaddr *)&client, clen);

        if (strncmp(str, "end", 3) == 0)
            break;
    }

    close(sn);
    return 0;
}
