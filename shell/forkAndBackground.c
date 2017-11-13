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
#include "forkAndBackground.h"
#include "mytoc.h"

char* concatenateFB(char**userIn,char*path, int pipeIndicator);
int countBeforeAmp(char**userIn);
char buff[10000];

/*Forks and attempts to execute instructions*/
void forkAndBackground(char**argv){
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
			int beforeSp = countBeforeAmp(argv);
			char * newargv [beforeSp+1];
			int i =0;
			for(; i<beforeSp;i++){
				newargv[i]=argv[i];
			}
			newargv[beforeSp]=NULL;
			for(int j=0;arr[j]!=NULL;j++){
				char * firstCommand []={argv[0],NULL};
				concat=concatenateFB(firstCommand,arr[j],0);
				// printf("After concatenation: %s \n", concat);
				newargv[0]=concat;
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
}

/*Concatenates input string to run single input commands 
with corresponding path.(e.g. ls)*/
char* concatenateFB(char**userIn,char*path, int pipeIndicator){
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

int countBeforeAmp(char**userIn){
	int count = 0;
	for(int i =0;userIn[i]!=NULL;i++){
		for(int j =0; userIn[i][j]!='\0';j++){
			if(userIn[i][j]=='&'){
				return count;
			}
			if(j==0){
				count++;
			}
		}
	}
	return count;
}