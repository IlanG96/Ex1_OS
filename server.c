#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include<arpa/inet.h>
#define Port 5566

void Start_server(){
    char *ip = "127.0.0.1";
    int server_socket, client_socket, msg;
    int connnected=0;
    struct sockaddr_in server_address , client_addr;
    int add_len=sizeof(server_address);
    char buffer[1024]; 
    server_socket = socket(AF_INET,SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("socket failed");
        exit(1);
    }

     printf("TCP socket is up.\n");

    int enableReuse=1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR,&enableReuse,sizeof(enableReuse))< 0)
    {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(1);
    }
    memset(&server_address, '\0', sizeof(server_address));    
    server_address.sin_addr.s_addr=inet_addr(ip);
    server_address.sin_family=AF_INET;
    server_address.sin_port=Port;    
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
        if(connnected==0){
        socklen_t len = sizeof(client_addr);
        //if(
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &len);//==-1)
        // {
        //     perror("accept error");
        //     exit(1);
        // }
        connnected=1;
        printf("User connected\n");
        }
        //while (connnected)
        //{
            bzero(buffer,1024);
            if(!recv(client_socket,buffer,1024,0)){
               //close(client_socket);
               connnected=0;
            }
            // printf("msg=%d",msg);
            // if (msg==0)
            // {
            //     connnected=0;
            // }
            else{
                for (int i = 0; i < 1024; i++)
                {
                    printf("%c", buffer[i]);
                }
            }
            
        //}
                
        
    }
    //close(client_socket);

    
}

int main(int argc, char const *argv[])
{
  Start_server();
    return 0;
}