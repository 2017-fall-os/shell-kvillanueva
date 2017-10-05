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
int forkAndExecuteWithPipes(char**argv){
	char buf[10000];
	int *pipeFds;
	pipeFds = (int *) calloc(2, sizeof(int));
	char *envp[] = {getenv("PATH"),NULL};
	pipe(pipeFds);
	int pid,pid2;
	int retVal=0;
	int retVal2=0;
	/*Initiates first fork to run first command (e.g. /bin/ls)*/
	pid = fork();
	if(pid==0){
		char* newargv []={argv[0],NULL};
		close(1);
		dup(pipeFds[1]);
		close(pipeFds[0]);
		close(pipeFds[1]);
		retVal=execve(argv[0],newargv,envp);
		printf("command not found \n");
		printf("Program terminated with exit code %d. \n", retVal);
		exit(2);
	}
	else{
		int waitVal, waitStatus;
		waitVal = waitpid(pid, &waitStatus, 0);
		if(waitVal == pid) {
			// printf("Gets to first waitval comparison\n");
			pid2 = fork();
			// char * newargv []={argv[2],NULL};
			char buf[1000];
			close(0);
			dup(pipeFds[0]);
			close(pipeFds[0]);
			close(pipeFds[1]);
			/*Second fork to initiate second command(e.g. /usr/bin/wc)*/
			if(pid2==0){
				// printf("Gets to next fork\n");
				if(argv[3]==NULL){
					/*Executs commands similar to /usr/bin/sort */
					char * newargv []={argv[2],NULL};
					// fgets(buf, 100, stdin);
					// printf("parent read <%s> from child\n", buf);
					retVal2 = execve(argv[2],newargv,NULL);
				}
				// else{
				// 					/*Executs commands similar to /usr/bin/sort -r */
				// 					char * newargv []={argv[2],argv[3],NULL};
				// 					// fgets(buf, 100, stdin);
				// 					// 				printf("parent read <%s> from child\n", buf);
				// 					retVal2 = execve(argv[2],newargv,NULL);
				// 				}
				printf("command not found \n");
				printf("Program terminated with exit code %d. \n", retVal2);
				exit(1);
			}
			else {
				int waitVal2, waitStatus2;
				waitVal2 = waitpid(pid2,&waitStatus2, 0);
				// if(waitVal2 == pid2) {
					/*Terminates process and shell
					Without this command would continue
					to loop and print(will fix in next
					itteration)*/
				// printf("Gets to next waitval comparison %d %d\n",waitVal2, pid2);
				close(pipeFds[0]);
				close(pipeFds[1]);
				return 1;
				// }
			}
		}
	}
	close(pipeFds[0]);
	close(pipeFds[1]);
	return 1;
}