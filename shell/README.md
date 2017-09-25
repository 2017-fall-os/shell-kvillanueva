# os-shell-lab-2-Part-1
# Source code by Kristian Villanueva

## Introduction

•Utilizing the tokenizer from lab 1, lab 2 part 1 is intended to execute bin commands in two different formats (e.g. /bin/ls,ls).

## Code Directory

•test.c: Reguests and reads in user input and sends the whole string to mytoc()
•mytoc.c: Separates the whole string into separate tokens based on entered
delimiter, then sends values to forkAndExecute.c to execute user input.
•forkAndExecute.c: Attempts to execute commands entered in test.c. Works for tow different formats (e.g. /bin/ls,ls);
however calls to some commands, such as date, return some errors. 
•helloWorld.c: test executable file. Runs when hi is entered in command line.
•forkAndExecute.h: Header file that declares the forkAndExecute() function in forkAndExecute.c
•mytoc.h: Header file that declares the mytoc() function in mytoc.c
•Makefile: contains compilation and run instructions for test.c, mytoc.c, helloWorld.c, and forkAndExecute.c.

## Compilation and run insturctions

•Compilation: With Makefile in the same directory, type make to compile files
•Run: After compilation, type ./test, and the program will run.
•Test: Commands of the type /bin/ls wokr correctly. Single commands of the type ls do not mirror /bin commands. 
Enterring hi will test running an executable file. 
•Type exit to exit shell