/*Lab2: Shell-Part1
  Name: Kristian Villanueva
  Last Modification: 9/24/17
 */
#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include "mytoc.h"
#include "forkAndExecute.h"
#define MAXLINE 1000
int terminationCheck(char input []);

int main(){
	/*Initial declaration for userInput and the receiving
	  variable tokenArr from call to mytoc()*/
	char userInput [MAXLINE];
	char **tokenArr;

	/*Loop requesting user input and calling mytoc() for
	  corresponding input. Quits when exit is typed.
	 */
	do{
		write(1, "$ \n",2);
		read(0, userInput, MAXLINE);
		/*Checks if exit was typed prior to calling mytoc()*/
		if(terminationCheck(userInput) != 0){
			tokenArr = mytoc(userInput, ' ');
			free(tokenArr);
		}
	}while(terminationCheck(userInput) != 0 || userInput[0]=='\n');
	return 0;
}

/*Checks if exit is typed into terminal*/
int terminationCheck(char input []){
	char exit []="exit";
	int sum1=0;
	int sum2=0;
	for(int i =0; i<4 && input[i]!='\n'; i++){
		if(exit[i]!=input[i]){
			return 1;
		}
		else{
			sum1 += exit[i];
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
