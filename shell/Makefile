all: test

CFLAGS = -g -O2

test: test.o mytoc.o forkAndExecute.o 
	cc -o test test.o mytoc.o forkAndExecute.o 

helloWorld: helloWorld.o
	cc -o helloWorld.o

clean:
	rm -f  *.o test

demo: test
	./test