#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define	MAX_SIZE_CMD	256
#define	MAX_SIZE_ARG	16

char cmd[MAX_SIZE_CMD];				// string holder for the command
char *argv[MAX_SIZE_ARG];			// an array for command and arguments
//pid_t pid;										// global variable for the child process ID
char i;	
int const ZERO = 0 ;											// global for loop counter

void get_cmd();								// get command string from thlle user
void convert_cmd();						// convert the command string to the required format by execvp()
void Start_shell();								// to start the shell
int open_localhost();

int StartsWith(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}

int main(){

	// start the shell
	Start_shell();

	return 0;
}

void echo(int sock , char* command, int command_size , int flag ){
			
			if( flag == 0)
            printf("%s\n",cmd);
			else
			send (sock,command,command_size,ZERO);
        
}

void Start_shell(){
	int flag = 0;
	int conn=0;
	while (1)
	{
	
		// get the command from user
		get_cmd();
		//printf("%s\n", cmd);
		// bypass empty commands
		// if(!strcmp("", cmd)) continue;

		// check for "exit" command
        if(!strcmp("EXIT", cmd)) break;

        if(!strcmp("getcwd", cmd)){
            getcwd(cmd,MAX_SIZE_CMD);
            printf("%s\n",cmd);
        }
        if(StartsWith(cmd,"ECHO ")){
            strncpy(cmd, cmd + 5, sizeof(cmd) - 5);
			echo(conn,cmd,strlen(cmd),flag);
		}
		if(!strcmp(cmd, "TCP")){
			//printf("here!");
			int conn = open_localhost();
			if (conn == 1){
				flag = 1;
			}
		}
			if(!strcmp(cmd, "LOCAL")){
			flag=0;
			close(conn);
		}


		// fit the command into *argv[]
		//convert_cmd();


		// fork and execute the command
		// pid = fork();
		// if(-1 == pid){
		// 	printf("failed to create a child\n");
		// }
		// else if(0 == pid){
		// 	// printf("hello from child\n");
		// 	// execute a command
		// 	execvp(argv[0], argv);
		// }
		// else{
		// 	// printf("hello from parent\n");
		// 	// wait for the command to finish if "&" is not present
		// 	if(NULL == argv[i]) waitpid(pid, NULL, 0);
		// }
	}
}
 
int open_localhost(){
	int sock=0;
	struct sockaddr_in server;
	if ((sock = socket(AF_INET, SOCK_STREAM, ZERO)) < ZERO )
	{
			printf("error creating socket");
			return -1;
	}
	
	server.sin_family = AF_INET;
	server.sin_port = 8080;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(connect(sock,( struct sockaddr * )&server, sizeof(server) < 0 )){
		printf( " error connection ");
		return -1;
	}
return 1;
}
	

void get_cmd(){
	// get command from user
	printf("Enter your commend>\t");
	//fgets(cmd, MAX_SIZE_CMD, stdin);
	scanf("%s",cmd);
	// remove trailing newline
	// if ((strlen(cmd) > 0) && (cmd[strlen (cmd) - 1] == '\n'))
    //     	cmd[strlen (cmd) - 1] = '\0';

	//printf("%s\n", cmd);
}

void convert_cmd(){
	// split string into argv
	char *ptr;
	i = 0;
	ptr = strtok(cmd, " ");
	while(ptr != NULL){
		//printf("%s\n", ptr);
		argv[i] = ptr;
		i++;
		ptr = strtok(NULL, " ");
	}

	// check for "&"
	if(!strcmp("&", argv[i-1])){
	argv[i-1] = NULL;
	argv[i] = "&";
	}else{
	argv[i] = NULL;
	}
	//printf("%d\n", i);
}

