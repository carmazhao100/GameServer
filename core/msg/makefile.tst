CC = g++
INCLUDE = .
CFLAGS = -g -Wall -ansi
MSGLIB = msglib.a

all:test
test:test.o command.o sys.o
	$(CC) -o test command.o test.o -l pthread
test.o:test.cpp command.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c test.cpp
command.o:command.cpp command.h ../sys.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c command.cpp
sys.o:../sys.h ../sys.c
	$(CC) -I$(INCLUDE) $(CFLAGS) -c ../sys.c
	
rma:
	-rm *.a
	
cleanAll:
	-rm  *.o *.a
