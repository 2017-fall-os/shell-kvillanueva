/*Lab2: Shell-Part2
Name: Kristian Villanueva
Last Modification: 10/1/17
*/
#include <stdio.h>
#include<unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "forkAndExecute.h"
#include "mytoc.h"
/*attempts to execute pipe commands*/
void forkAndExecuteWithPipes(char**argv){
	char buf[10000];
	int *pipeFds;
	pipeFds = (int *) calloc(2, sizeof(int));
	char *envp[] = {getenv("PATH"),NULL};
	pipe(pipeFds);
	int pid;
	int retVal=0;
	int retVal2=0;
	/*Initiates first fork to run first command (e.g. /bin/ls)*/
	pid = fork();
	if(pid==0){
		char* newargv []={argv[0],NULL};
		close(1);
		dup2(pipeFds[1],1);
		close(pipeFds[0]);
		close(pipeFds[1]);
		retVal=execve(argv[0],newargv,envp);
		printf("command not found \n");
		printf("Program terminated with exit code %d. \n", retVal);
		exit(2);
	}
	else{
		char * newargv []={argv[2],NULL};
		close(0);
		dup2(pipeFds[0],0);
		close(pipeFds[0]);
		close(pipeFds[1]);
		printf("Gets to next fork\n");
		/*Second fork to initiate second command(e.g. /usr/bin/wc)*/
		pid = fork();
		if(pid==0){
			if(argv[3]==NULL){
				/*Executs commands similar to /usr/bin/sort */
				char * newargv []={argv[2],NULL};
				retVal2 = execve(argv[2],newargv,NULL);
			}
			else{
				/*Executs commands similar to /usr/bin/sort -r */
				char * newargv []={argv[2],argv[3],NULL};
				retVal2 = execve(argv[2],newargv,NULL);
			}
			printf("command not found \n");
			printf("Program terminated with exit code %d. \n", retVal2);
			exit(2);
		}
		
		else {
			int waitVal, waitStatus;
			waitVal = waitpid(pid,&waitStatus, 0);
			if(waitVal == pid) {
				/*Terminates process and shell
				  Without this command would continue
				  to loop and print(will fix in next
				  itteration)*/
				exit(0);
				// printf("Gets to next waitval comparison %d %d\n",waitVal, pid);
				return;
			}
			return;
		}
		int waitVal, waitStatus;
		waitVal = waitpid(pid, &waitStatus, 0);
		if(waitVal == pid) {
			printf("Gets to next waitval comparison\n");
			return;
		}
		return;
	}
	return;
}