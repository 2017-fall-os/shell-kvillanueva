/*Lab2: Shell-Part1
Name: Kristian Villanueva
Last Modification: 9/24/17
*/
#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "forkAndExecute.h"
#include "mytoc.h"

char* concatenate(char**userIn,char*path);
char buff[10000];

/*Forks and attempts to execute instructions*/
int forkAndExecute(char**argv){
	int pid;
	int retVal=0;
	int retVal2=0;
	char *envp[] = {getenv("PATH"),NULL};
	pid = fork();
	if (pid == 0) {		/* child */
		/*Attempts to execute /bin type commands*/
		retVal = execve(argv[0],&argv[0],envp);
		/*Attempts to execute single input commands (e.g. ls)*/
		if(retVal == -1){
			int pathLength1 = 5;
			char *concat;
			// printf("%s \n",getenv("PATH"));
			char *path;
			path=getenv("PATH");
			// printf("test path %s", path);
			char **arr;
			arr=mytoc(path,':');
			
			for(int j=0;arr[j]!=NULL;j++){
				concat=concatenate(argv,arr[j]);
				// printf("After concatenation: %s \n", concat);
				char* newargv[]={concat,NULL};
				retVal2 = execve(concat,newargv,NULL);
			}
			// concat=concatenate(argv,"/bin/");
			// printf("After concatenation: %s \n", concat);
			// retVal2 = execve(concat,&concat,envp);
			free(arr);
		}
		// /*Attempts to execute hi command for executable helloWorld.c*/
		// 		if(retVal2 == -1 && argv[0][0]=='h'&&argv[0][1]=='i'&&tArrLength<3){
		// 			int retVal3 = execve("./helloWorld",&argv[0],envp);
		// 		}
		
		printf("command not found \n");
		printf("Program terminated with exit code %d. \n", retVal);
		close(1);
		exit(2);
	} else { 			/* parent */
		int waitVal, waitStatus;
		waitVal = waitpid(pid, &waitStatus, 0);
		if (waitVal == pid) {
			return retVal;
			close(0);
		}
		return retVal;
		close(0);
	}
}

/*Concatenates input string to run single input commands (e.g. ls)*/
char* concatenate(char**userIn,char*path){
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


