#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#define SERVER_PORT 1025
#define SERVER_IP "127.0.0.1"

int main()
{
    struct sockaddr_in server, client;
    int sd, len, newsd;
    char msg1[1024], msg2[] = "Bad request", *ptr;
    time_t t;
    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    sd = socket(AF_INET,SOCK_STREAM,0);
    bind(sd, (struct sockaddr *)&server, sizeof(server));
    listen(sd, 5);
    len = sizeof(client);
    printf("Time server is running...\n");
    while(1)
    {
        newsd = accept(sd,(struct sockaddr *)&client,&len);
        do{
            memset(msg1,0x0,sizeof(msg1));
            recv(newsd,msg1,sizeof(msg1), 0);
            if (strcmp(msg1, "time") == 0){
                t = time(NULL);
                ptr = ctime(&t);
                send(newsd,ptr,strlen(ptr) + 1, 0);
                }
            else{
                send(newsd,msg2,strlen(msg2) + 1, 0);
            }
        } while (strcmp(msg1,"stop"));
        close(newsd);
    }
    return 0;
}
