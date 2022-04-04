#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include<arpa/inet.h>
#define Port 5566

void Start_server(){
  printf("here!");
    printf("here!");
    printf("here!");
    printf("here!");
    char *ip = "127.0.0.1";
    int server_socket, client_socket, msg;
    int connnected=0;
    struct sockaddr_in server_address , client_addr;
    int add_len=sizeof(server_address);
    char buffer[1024]; 
    printf("here!");
    server_socket = socket(AF_INET,SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("socket failed");
        exit(1);
    }

     printf("TCP socket is up.\n");

    // int enableReuse=1;
    // if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR,&enableReuse,sizeof(enableReuse))< 0)
    // {
    //     perror("setsockopt(SO_REUSEADDR) failed");
    //     exit(1);
    // }
    printf("ILAN AMAR LERSHOM PO");
    server_address.sin_addr.s_addr=inet_addr(ip);
    server_address.sin_family=AF_INET;
    server_address.sin_port=(5566);    
    int bind_server = bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));
    if (bind_server < 0)
    {
        perror("Bind failed");
        exit(1);
    }
    printf("BIND SUCSSES\n");

    listen(server_socket,3);
    printf("listening...\n");
    
    while (1)
    {
        printf("ILAN AMAR LERSHOM PO");
         socklen_t len = sizeof(client_addr);
        if(client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &len)==-1)
        {
            perror("accept error");
            exit(1);
        }
        printf("client connect\n");
        connnected=1;
        printf("%d", connnected);
        while (connnected)
        {
            printf("OTOT");
            memset(buffer,0,1024);
            msg=read(client_socket,buffer,1024);
            printf("msg=%d",msg);
            if (msg==0)
            {
                connnected=0;
            }
            else
                printf("%s \n",buffer);
            
        }
                
        
    }
    //close(client_socket);

    
}

int main(int argc, char const *argv[])
{
  Start_server();
    return 0;
}