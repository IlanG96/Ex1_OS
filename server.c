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

    int server_socket, client_socket, msg;
    int connnected=0;
    struct sockaddr_in server_address;
    int add_len=sizeof(server_address);
    char buffer[100]={0}; 
    printf("here!");
    if ((server_socket = socket(AF_INET,SOCK_STREAM, 0))  == 0)
    {
        perror("socket failed");
        exit(1);
    }
    int enableReuse=1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR,&enableReuse,sizeof(enableReuse))< 0)
    {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(1);
    }
    printf("ILAN AMAR LERSHOM PO");
    server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(Port);    
    if (bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address))<0)
    {
        perror("Bind failed");
        exit(1);
    }
    if (listen(server_socket,3)<0)
    {
        perror("listen error");
        exit(1);
    }
    printf("ILANDSFDSF");
    while (1)
    {
        printf("ILAN AMAR LERSHOM PO");
        if (client_socket= accept(server_socket,(struct sockaddr*)&server_address,(socklen_t*)&add_len)<0)
        {
            perror("accept error");
            exit(1);
        }
        printf("client connect");
        connnected=1;
        while (connnected)
        {
            memset(buffer,0,sizeof(buffer));
            msg=read(client_socket,buffer,sizeof(buffer));
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