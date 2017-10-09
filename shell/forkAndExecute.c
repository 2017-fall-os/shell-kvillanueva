/*Lab2: Shell-Part2
Name: Kristian Villanueva
Last Modification: 10/8/17
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

char* concatenate(char**userIn,char*path, int pipeIndicator);
// int containsPipe(char**userIn);
char buff[10000];

/*Forks and attempts to execute instructions*/
void forkAndExecute(char**argv){
	int *pipeFds;
	pipeFds = (int *) calloc(2, sizeof(int));
	pipe(pipeFds);
	int pid;
	int pid2;
	int retVal=0;
	int retVal2=0;
	int didFirstExec=0;
	char *envp[] = {getenv("PATH"),NULL};
	char *concat;
	pid = fork();
	if (pid == 0) {		/* child */
		/*Attempts to execute /bin type commands*/
		retVal = execve(argv[0],&argv[0],envp);
			
		/*Attempts to execute single input commands (e.g. ls)*/
		if(retVal == -1){
			char *path;
			path=getenv("PATH");
			char **arr;
			arr=mytoc(path,':');
			for(int j=0;arr[j]!=NULL;j++){
				concat=concatenate(argv,arr[j],0);
				// printf("After concatenation: %s \n", concat);
				char* newargv[]={concat,NULL};
				retVal2 = execve(concat,newargv,NULL);
			}
			free(arr);
		}
		/*Attempts to execute hi command for executable helloWorld.c*/
		if(retVal2 == -1 && argv[0][0]=='h'&&argv[0][1]=='i'&&argv[0][2]=='\0'&&argv[1]==NULL){
			int retVal3 = execve("./helloWorld",&argv[0],envp);
		}
		printf("command not found \n");
		printf("Program terminated with exit code %d. \n", retVal);
		close(0);
		exit(2);
	}
	else { 			/* parent */
		int waitVal, waitStatus;
		waitVal = waitpid(pid, &waitStatus, 0);
		if (waitVal == pid) {
			return;
			close(0);
		}
		return;
		close(0);
	}
}

/*Concatenates input string to run single input commands 
  with corresponding path.(e.g. ls)*/
char* concatenate(char**userIn,char*path, int pipeIndicator){
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