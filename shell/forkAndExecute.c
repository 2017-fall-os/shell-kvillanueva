#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "forkAndExecute.h"

char* concatenate(char**userIn,char*path, int tArrLength,
		int * tokenLengthsArr, int pathLength);
char buff[1000];

/**/
int forkAndExecute(char**argv,int tArrLength,int * tokenLengthsArr){
	//	char *args[2];
	//	args[0] = &argv[0][0];
	//	args[1] = &argv[1][0];
	int pid;
	int retVal=0;
	int retVal2=0;
	char *envp[] = {"/bin/",NULL};
	char *envp2[] = {NULL};
	pid = fork();
	if (pid == 0) {		/* child */
		retVal = execve(argv[0],&argv[0],envp);
		if(retVal == -1){
			//			printf("Tried concat \n");
			int pathLength1 = 5;
			char *concat;


			concat=concatenate(argv,envp[0],tArrLength,
					tokenLengthsArr,pathLength1);
			
			//printf("After concatenation: %s \n", concat);
			//			printf("was inside concat \n");
			retVal2 = execve(concat,&concat,envp2);
		}
//		if(retVal2 == -1){
//			printf("Tried hello \n");
//			int retVal3 = execve("helloWorld.o",&argv[0],envp);
//		}
		//		if(retVal == -1){
		//			execvp(argv[0],&argv[0]);
		//		}
		printf("command not found \n");
		printf("Program terminated with exit code %d. \n", retVal);
		close(1);
		exit(2);
	} else { 			/* parent */
		//free(concat);
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

char* concatenate(char**userIn,char*path, int tArrLength,
		int * tokenLengthsArr, int pathLength){
	//	printf("Was in concat \n");
	
	int i =0;
	for(; i<pathLength && path[i]!= '\0';i++){
		buff[i]=path[i];
	}
	for(int j=0;j<tArrLength;j++,j++){
		for(int k=0;k<tokenLengthsArr[j]&&userIn[j][k]!='\0';k++){
			buff[i]=userIn[j][k];
			i++;
		}
	}
	buff[i]='\0';
	//concat = malloc(i);
	//printf("After concatenation(still in func): %s \n", buff  );
	return buff;
}


