/*Lab2: Shell-Part2
Name: Kristian Villanueva
Last Modification: 10/8/17
*/
#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include "mytoc.h"
#include "forkAndExecute.h"
#include "forkAndExecuteWithPipes.h"
#include "forkAndBackground.h"
#define MAXLINE 10000
int terminationCheck(char input []);
int containsPipe(char**userIn);
int containsCD(char**userIn);
int containsAmpersand(char**userIn);
int main(){
	/*Initial declaration for userInput and the receiving
	variable tokenArr from call to mytoc()*/
	char userInput [MAXLINE];
	char **tokenArr;
	int check =0;

	/*Loop requesting user input and calling mytoc() for
	corresponding input. Quits when exit is typed.
	*/
	do{
		write(0, "$ \n",2);
		int bytesRead = read(0, userInput, MAXLINE);
		if(bytesRead==0){
			exit(0);
		}
		/*Checks if exit was typed prior to calling mytoc()*/
		if(terminationCheck(userInput) != 0 && userInput[0]!='\n'){
			tokenArr = mytoc(userInput, ' ');
			if(containsCD(tokenArr)==1){
				chdir(tokenArr[1]);
			}
			else if(containsAmpersand(tokenArr)==1){
				forkAndBackground(tokenArr);
			}
			else if(containsPipe(tokenArr)==1){
				// char **tokenizedPipe=mytoc(userInput, '|');
				check = forkAndExecuteWithPipes(tokenArr); 
				// free(tokenizedPipe);
			}
			else{
				forkAndExecute(tokenArr);
			}			
			free(tokenArr);
		}
	}while(terminationCheck(userInput) != 0 || userInput[0]=='\n');
	return 0;
}

/*Checks if exit is typed into terminal*/
int terminationCheck(char input []){
	char exit []="exit";
	int sum1=0;
	for(int i =0; i<4; i++){
		sum1 += input[i];
	}
	int sum2=0;
	for(int i =0;input[i]!='\n'; i++){
		if(exit[i]!=input[i]){
			return 1;
		}
		else{
			sum2 += input[i];
		}
	}
	if(sum1==sum2){
		return 0;
	}
	else{
		return 1;
	}
}

int containsPipe(char**userIn){
	// printf("Got to containsPipe\n");
	for(int j=0;userIn[j]!=NULL;j++){
		for(int k=0;userIn[j][k]!='\0';k++){
			if(userIn[j][k]=='|'){
				return 1;
			}
		}
	}
	return 0;
}

int containsAmpersand(char**userIn){
	// printf("Got to containsPipe\n");
	for(int j=0;userIn[j]!=NULL;j++){
		for(int k=0;userIn[j][k]!='\0';k++){
			if(userIn[j][k]=='&'){
				return 1;
			}
		}
	}
	return 0;
}

int containsCD(char**userIn){
	// printf("Got to containsPipe\n");
	if(userIn[0][0]=='c' && userIn[0][1]=='d'&& userIn[0][2]=='\0'){
		return 1;
	}
	return 0;
}
