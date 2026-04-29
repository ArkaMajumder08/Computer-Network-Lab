#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<unistd.h>
#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4000

int main(){
    struct sockaddr_in server ={0} ,client ;
    int sd,len,newS,pid,clen = sizeof(client);
    char str[512] ;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    sd = socket(AF_INET ,SOCK_DGRAM ,0);

    int ex = bind(sd , (struct sockaddr *)&server ,sizeof(server));

    printf("UDP DAYTIME SERVER IS ONLINE...!\n");
    while(1){
        recvfrom(sd,str,512,0,(struct sockaddr *)&client ,&clen);

        time_t now = time(NULL);
        char *time_str = ctime(&now);

        sendto(sd ,time_str,strlen(time_str)+1,0,(struct sockaddr *)&client , clen);
    }
    close(sd);
    return 0;
}
