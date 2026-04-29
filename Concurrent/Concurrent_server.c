#include<stdio.h>
#include<string.h>
#include <strings.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define SERVER_IP "127.0.0.1"

#define SERVER_PORT 9400

int main(){
    struct sockaddr_in client , server;
    int sd,newSocket,pid,clen = sizeof(client);
    char str[512]; // buffer for message

    bzero((char *)&server ,sizeof(server)); //set all bytes of server struct to 0

    server.sin_family = AF_INET;   // IPv4
    server.sin_addr.s_addr=inet_addr(SERVER_IP);  // convert IP string → binary
    server.sin_port = htons(SERVER_PORT);        // host → network byte order

    sd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET → IPv4
    // SOCK_STREAM → TCP

    bind(sd , (struct sockaddr *)&server ,sizeof(server));
    listen(sd, 5);

    while(1){
        printf("Server is waiting\n");
        newSocket = accept(sd ,(struct sockaddr *)&client ,&clen); // new socket client communication
        pid=fork();
        if(pid ==0){ // child handles client
            printf("File connected !\n");
            do{
                memset(str,0x0,512); // clear buffer
                recv(newSocket,str,512,0); // receive data from client
                send(newSocket,str,strlen(str)+1,0); // send same data back (echo)

                printf("Received message : %s\n" ,str);
                fflush(stdout);
            }while(strcmp(str,"stop")); // until client sends "stop"
        }else if(pid>0){
            close(newSocket);
        }else{
            printf("No concurrency !");
        }
    }
    return 0;
}
