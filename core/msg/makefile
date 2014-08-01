CC = g++
INCLUDE = .
CFLAGS = -g -Wall -ansi
MSGLIB = msglib.a

all:rma $(MSGLIB)
$(MSGLIB):$(MSGLIB)(command.o) $(MSGLIB)(proxyMsg.o) $(MSGLIB)(msgCenter.o) $(MSGLIB)(proxyCenter.o) 

proxyCenter.o:proxyCenter.cpp Iproxy.h  proxyCenter.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c proxyCenter.cpp
proxyMsg.o:proxyMsg.cpp proxyMsg.h ../sys.h ../objPool.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c proxyMsg.cpp
command.o:command.cpp command.h ../sys.h ../objPool.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c command.cpp
msgCenter.o:msgCenter.cpp msgCenter.h command.h Imediator.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c msgCenter.cpp
	
rma:
	-rm *.a
	
cleanAll:
	-rm  *.o *.a
