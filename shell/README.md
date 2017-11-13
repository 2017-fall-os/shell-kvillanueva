# os-shell-lab-2-Part-2
# Source code by Kristian Villanueva

## Introduction

•Utilizing the tokenizer from lab 1, lab 2 part 2 is intended to execute bin commands in two different formats (e.g. /bin/ls,ls), pipe commands, background tasks, and directory changes.

## Code Directory

•test.c: Reguests and reads in user input and sends the whole string to mytoc()
•mytoc.c: Separates the whole string into separate tokens based on entered
delimiter, then sends values to forkAndExecute.c to execute user input.
•forkAndExecute.c: Attempts to execute commands entered in test.c. Works for two different formats (e.g. /bin/ls,ls).
•forkAndExecuteWithPipes.c: is used when test.c detects a '|' in the returned pointer to pointer array.
Once detected an initial fork attempts to execute the first command (e.g. /bin/ls or ls). If execution is succesful the second command is attempted by forking in the else statement and then executing within this fork (e.g. /usr/bin/wc or wc).(I found the fork within the else statement in this stack overvflow post: https://stackoverflow.com/questions/36585896/piping-two-child-processes-one-for-ls-the-other-for-sort-but-sort-is-not-work)
•forkAndBackground.c: used to execute background tasts
•helloWorld.c: test executable file. Runs when hi is entered in command line.
•forkAndExecute.h: Header file that declares the forkAndExecute() function in forkAndExecute.c
•forkAndExecuteWithPipes.h: Header file that declares the forkAndExecuteWithPipes() function in forkAndExecuteWithPipes.c
•forkAndBackground.h: Header file that declares the forkAndBackground() function in forkAndBackground.c
•mytoc.h: Header file that declares the mytoc() function in mytoc.c
•Makefile: contains compilation and run instructions for test.c, mytoc.c, helloWorld.c, and forkAndExecute.c.

## Compilation and run insturctions

•Compilation: With Makefile in the same directory, type make to compile files
•Run: After compilation, type ./test, and the program will run.
•Test: Commands of the type /bin/ls and ls work correctly. Pipe commands work as well. cd and background tasks are working as well. 
Enterring "hi" will test running an executable file within the shell. 
•Type exit to exit shell

## Test Issues
Using testShell.sh, pipe does not work correctly (cat /etc/passwd | sort); however manually typing that command into my shell does work.

Using testShell.sh cd does not work (cd ..), but it does work when I manually type it into my shell.

Using testShell.sh background tasks do not work correctly, and typing (bash < /tmp/c1 &) in my shell does not work correctly; however typing the test command from github (find /etc -print &) or (ping google.com &) does work correctly