EFILES= test helloWorld
all: $(EFILES)

CFLAGS = -g -O2

test: test.o mytoc.o forkAndExecute.o forkAndExecuteWithPipes.o forkAndBackground.o
	cc -o test test.o mytoc.o forkAndExecute.o forkAndExecuteWithPipes.o forkAndBackground.o

helloWorld: helloWorld.o

clean:
	rm -f  *.o test helloWorld
