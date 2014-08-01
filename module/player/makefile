CC = g++
INCLUDE = .
CFLAGS = -g -Wall -ansi
PLAYERLIB = playerlib.a

all:rma $(PLAYERLIB)
$(PLAYERLIB):$(PLAYERLIB)(role.o) \
	     $(PLAYERLIB)(roleCtrMediator.o) \
	     $(PLAYERLIB)(roleCtr.o) \
	     $(PLAYERLIB)(roleCtrProxy.o)

role.o:role.cpp \
	role.h \
	../../core/sys.h \
	../../Facade.h \
	../../core/NetMsg.h \
	roleCtr.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c role.cpp
roleCtrMediator.o:roleCtrMediator.h \
		roleCtrMediator.cpp \
		../../core/sys.h \
		../../Facade.h \
		roleCtr.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c roleCtrMediator.cpp
roleCtrProxy.o:roleCtrProxy.h \
		roleCtrProxy.cpp \
		roleCtr.h \
		../../core/sys.h \
		../../msgConst.h \
		../../Facade.h \
		../../core/msg/command.h \
		../../core/msg/Iproxy.h \
		../../core/NetMsg.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c roleCtrProxy.cpp
roleCtr:roleCtr.h \
	roleCtrcpp \
	../../core/sys.h \
	roleCtrProxy.h \
	../../core/gsSocket.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c roleCtr.cpp

rma:
	-rm *.a
	
cleanAll:
	-rm  *.o *.a
