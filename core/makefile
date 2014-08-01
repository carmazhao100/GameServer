CC = g++
AR    =      ar
RM    =      rm
CP    =      cp
ECHO =      echo

INCLUDES = -I./
INCLUDE = .
CFLAGS = -g -Wall -ansi
CFLAGS     += -O2 $(INCLUDES)
#定义目标
CORELIB = corelib.a
#定义库的名字们
MSGLIB = msglib.a
#定义目标的依赖
OBJS = gsSocket.o gsThread.o gsQueue.o gsTimer.o gsSQL.o NetMsg.o sys.o
LIBS = $(MSGLIB)


include tool.mk

all:rma $(CORELIB)

gsSocket.o:gsSocket.cpp gsSocket.h sys.h msg/proxyMsg.h gsQueue.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c gsSocket.cpp
gsThread.o:gsThread.h gsThread.cpp sys.h  gsSocket.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c gsThread.cpp
gsQueue.o:gsQueue.h gsQueue.cpp sys.h msg/proxyMsg.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c gsQueue.cpp
gsTimer.o:sys.h gsTimer.h gsTimer.cpp
	$(CC) -I$(INCLUDE) $(CFLAGS) -c gsTimer.cpp
gsSQL.o:gsSQL.cpp gsSQL.h sys.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c gsSQL.cpp
NetMsg.o:NetMsg.h NetMsg.cpp sys.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c NetMsg.cpp
sys.o:sys.c sys.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c sys.c

$(CORELIB):$(LIBS) $(OBJS)
	$(BUILD_LIBRARY)

$(MSGLIB):
	(cd msg;$(MAKE);cp $(MSGLIB) ../$(MSGLIB))
rma:
	-rm *.a
	
clean:
	-rm $(LIBS) $(OBJS)
