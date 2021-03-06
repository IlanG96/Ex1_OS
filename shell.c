#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dirent.h>

#define	MAX_SIZE_CMD	256
#define PORT 5514 // port for the TCP connection

char cmd[MAX_SIZE_CMD];				// string holder for the command
void get_cmd();								// get command string from the user
void Start_shell();								// to start the shell
int open_localhost();

/**
 * @brief A function to check if param a start with param b 
 * 
 * @return 1 if param a start with param b 
 */
int StartsWith(const char *a, const char *b)
{
   if(strncmp(a, b, strlen(b)) == 0) return 1;
   return 0;
}


/**
 * @brief Return all the file in the current directory
 * 
 */
void dir_files(){
	DIR *dir_explorer;
	struct dirent *curr_dir;
	dir_explorer = opendir(".");	
    if (dir_explorer!=NULL)
	{
		curr_dir= readdir(dir_explorer);
		while (curr_dir!= NULL)
		{
			printf("%s \n",curr_dir->d_name);
			curr_dir= readdir(dir_explorer);
		}
		
	}
	else{
		printf("ERR: directory opening failed");
		exit(1);
	}
	closedir(dir_explorer);
	return;    
}

/**
 * @brief create a copy of the file name entered in the cmd.
 * 
 * @param cmd the file name
 * @param cmd_len file name length
 */
	void Copy_func(char *cmd,int cmd_len){
		char src[MAX_SIZE_CMD];
		char dest[MAX_SIZE_CMD];
		int file_1_finished=0;
  		memset(&src, '\0', sizeof(src));
		memset(&dest, '\0', sizeof(dest));
		int index1=0;
		int index2=0;
		for (int i = 0; i < cmd_len; i++)
		{
			if (file_1_finished==0)
			{
				if (cmd[i]!=' ')
				{
					src[index1++]=cmd[i];
				}
				else{
					file_1_finished=1;
				}
				
			}
			else{
				dest[index2++]=cmd[i];
			}
		}
    	if (src == NULL ){
        	printf("Error: invalid src name\n");
        	return;
    	}
		if (dest == NULL)
		{
        	printf("Error: invalid dest name\n");
        	return;
		}
		char char_pointer;
    	FILE *fSrc = fopen(src, "r");
    	FILE *fDst = fopen(dest, "a");
    	while ((char_pointer = fgetc(fSrc)) != EOF) {
        	fputc(char_pointer, fDst);
    	}
    	printf("Copy finished\n");
    	fclose(fSrc);
    	fclose(fDst);				
	}

/**
 * @brief Main Function start the shell program
 * 
 */
void Start_shell(){
	int flag = 0;//	For the TCP connection
	int conn=0;
	while (1)
	{
	
		// get the command from user
		get_cmd();
		// check for "exit" command
        if(strncmp(cmd, "EXIT",4)==0){
			 printf("Bye!\n");
			 break;
			 }
        else if(StartsWith(cmd,"ECHO")){
            strncpy(cmd, cmd + 5, sizeof(cmd) - 5);
			if(flag == 0)
            printf("%s",cmd);
			else{
			send(conn , cmd, strlen(cmd),0);
			}
		}
		else if(strncmp(cmd, "TCP", 3) == 0){
			conn=open_localhost();
			flag = 1;
		}
		else if(StartsWith(cmd,"LOCAL")){
			flag=0;
			if(conn!=0){
			close(conn);}
		}
		else if (StartsWith(cmd,"DIR"))
		{
			dir_files();
		}
		else if (StartsWith(cmd,"CD"))
		{
			/**
			 * @brief chdir change the current directory the shell is in.
			 * which mean that chdir use the kernal to naviagte to the wished directory so this is a system call.
			 */
			strncpy(cmd, cmd + 3, sizeof(cmd) - 3);
			cmd[strlen(cmd)-1]='\0'; //remove the \n in the end of the file
			int x=chdir(cmd);
			if(x==-1)
				printf("Cannt open the dir\n");
		}
		else if(StartsWith(cmd,"COPY")){
			strncpy(cmd, cmd + 5, sizeof(cmd) - 5);
			Copy_func(cmd,strlen(cmd));
		}
		else if (StartsWith(cmd,"DELETE"))
		{
			/**
			 * @brief The unlink is a system call  
			 * 
			 */
			strncpy(cmd, cmd + 7, sizeof(cmd) - 7);
			cmd[strlen(cmd)-1]='\0';
			if (unlink(cmd))
			{
				printf("Failed to delete the file\n");
				printf("%s\n",cmd);
			}
			else
				printf("File deleted\n");
			
		}
		
		else{
			/**
			 * @brief Construct a new system object.
			 * System is a library function.
			 */
			//system(cmd);
		
            int pid = fork();
            if(pid<0){
                printf("Failed to fork");
                break;
            }
            if(pid==0){
                execl("/bin/sh", "sh", "-c", cmd, (char *) NULL);
                break;
            }else{
                wait(NULL);
            }

		}
	}
}
 
int open_localhost(){
    char *ip = "127.0.0.1";

  struct sockaddr_in addr;

  int Client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (Client_socket < 0){
    perror("ERR:Socket Creation");
    exit(1);
  }
  printf("Socket created.\n");

  memset(&addr, '\0', sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = PORT;
  addr.sin_addr.s_addr = inet_addr(ip);

  connect(Client_socket, (struct sockaddr*)&addr, sizeof(addr));
  printf("Connected to the server.\n");
  return Client_socket;
}
	

void get_cmd(){
	// get command from user
	printf("Enter your commend\n");
	getcwd(cmd,MAX_SIZE_CMD);
    printf("%s>",cmd);
	fgets(cmd, MAX_SIZE_CMD, stdin);
}

int main(){

	// start the shell
	Start_shell();

	return 0;
}
