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

char* concatenatePipes(char**userIn,char*path);
char buff[10000];
/*attempts to execute pipe commands*/
int forkAndExecuteWithPipes(char**argv){
	int stdout = dup(1);
	int stdin = dup(0);
	int *pipeFds;
	pipeFds = (int *) calloc(2, sizeof(int));
	char *envp[] = {getenv("PATH"),NULL};
	int pid,pid2;
	int retVal=0;
	int retVal2=0;
	int retVal3=0;
	int retVal4=0;
	
	char *concat;
	pipe(pipeFds);
	/*Initiates first fork to run first command (e.g. /bin/ls)*/
	pid = fork();
	if(pid==0){
		char* newargv []={argv[0],NULL};
		close(1);
		dup(pipeFds[1]);
		close(pipeFds[0]);
		close(pipeFds[1]);
		retVal=execve(argv[0],newargv,envp);
		if(retVal == -1){
			char *path;
			path=getenv("PATH");
			char **arr;
			arr=mytoc(path,':');
			for(int j=0;arr[j]!=NULL;j++){
				concat=concatenatePipes(newargv,arr[j]);
				// printf("After concatenation: %s \n", concat);
				char* newargv2[]={concat,NULL};
				retVal2 = execve(concat,newargv,NULL);
			}
			free(arr);
		}
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
			close(0);
			dup(pipeFds[0]);
			close(pipeFds[0]);
			close(pipeFds[1]);
			/*Second fork to initiate second command(e.g. /usr/bin/wc)*/
			if(pid2==0){
				if(argv[3]==NULL){
					/*Executs commands similar to /usr/bin/sort */
					char * newargv []={argv[2],NULL};
					retVal3 = execve(argv[2],newargv,NULL);
					if(retVal3 == -1){
						char *path;
						path=getenv("PATH");
						char **arr;
						arr=mytoc(path,':');
						for(int j=0;arr[j]!=NULL;j++){
							concat=concatenatePipes(newargv,arr[j]);
							// printf("After concatenation: %s \n", concat);
							char* newargv2[]={concat,NULL};
							retVal4 = execve(concat,newargv2,NULL);
						}
						free(arr);
					}
				}
				else{
					/*Executs commands similar to /usr/bin/sort -r */
					char * newargv []={argv[2],argv[3],NULL};
					retVal3 = execve(argv[2],newargv,NULL);
					if(retVal3 == -1){
						char *path;
						path=getenv("PATH");
						char **arr;
						arr=mytoc(path,':');
						for(int j=0;arr[j]!=NULL;j++){
							char * firstCommand []={argv[2],NULL};
							concat=concatenatePipes(firstCommand,arr[j]);
							// printf("After concatenation: %s \n", concat);
							char* newargv2[]={concat,argv[3],NULL};
							retVal4 = execve(concat,newargv,NULL);
						}
						free(arr);
					}
				}
				printf("command not found \n");
				printf("Program terminated with exit code %d. \n", retVal2);
				exit(1);
			}
			else {
				int waitVal2, waitStatus2;
				waitVal2 = waitpid(pid2,&waitStatus2, 0);
				dup2(stdin, 0);
				dup2(stdout, 1);
				close(stdin);
				close(stdout);
				return 1;
				// }
			}
		}
	}
	dup2(stdin, 0);
	dup2(stdout, 1);
	close(stdin);
	close(stdout);
	return 1;
}

/*Concatenates input string to run single input commands 
with corresponding path.(e.g. ls)*/
char* concatenatePipes(char**userIn,char*path){
	int i =0;
	for(;path[i]!='\0';i++){
		buff[i]=path[i];
	}
	buff[i]='/';
	i++;
	for(int j=0;userIn[j]!=NULL;j++){
		for(int k=0;userIn[j][k]!='\0';k++){
			buff[i]=userIn[j][k];
			i++;
		}
	}
	buff[i]='\0';
	// printf("After concatenation(still in func): %s \n", buff  );
	return buff;
}