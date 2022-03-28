#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define	MAX_SIZE_CMD	256
#define	MAX_SIZE_ARG	16

char cmd[MAX_SIZE_CMD];				// string holder for the command
char *argv[MAX_SIZE_ARG];			// an array for command and arguments
//pid_t pid;										// global variable for the child process ID
char i;												// global for loop counter

void get_cmd();								// get command string from the user
void convert_cmd();						// convert the command string to the required format by execvp()
void Start_shell();								// to start the shell

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

void Start_shell(){
	while(1){
		// get the command from user
		get_cmd();
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
            printf("%s\n",cmd);
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

void get_cmd(){
	// get command from user
	printf("Enter your commend>\t");
	fgets(cmd, MAX_SIZE_CMD, stdin);
	// remove trailing newline
	if ((strlen(cmd) > 0) && (cmd[strlen (cmd) - 1] == '\n'))
        	cmd[strlen (cmd) - 1] = '\0';
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

