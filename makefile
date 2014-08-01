CC = g++
INCLUDE = .
CFLAGS = -g -Wall -ansi
CORELIB = corelib.a
MODULELIB = modulelib.a


all:rma test
test:test.o Facade.o msgIdCtr.o msgConst.o $(CORELIB) $(MODULELIB)
	$(CC) -o test test.o Facade.o msgIdCtr.o msgConst.o $(CORELIB) $(MODULELIB) -l pthread -l mysqlclient -l stdc++
test.o:Facade.h test.cpp 
	$(CC) -I$(INCLUDE) $(CFLAGS) -c test.cpp

Facade.o:Facade.cpp \
	Facade.h \
	core/gsSocket.h \
	core/gsThread.h \
	core/sys.h \
	core/gsSQL.h \
	core/gsTimer.h \
	core/msg/proxyMsg.h \
	core/msg/command.h \
	core/msg/Iproxy.h \
	core/msg/Imediator.h \
	core/msg/msgCenter.h \
	core/msg/proxyCenter.h \
	module/player/roleCtrProxy.h \
	module/player/roleCtrMediator.h \
	module/map/mapCtr.h \
	module/map/mapCtrMediator.h \
	module/snapShot/snapShotCtr.h \
	module/snapShot/snapShotProxy.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c Facade.cpp
msgConst.o:msgConst.h msgConst.cpp
	$(CC) -I$(INCLUDE) $(CFLAGS) -c msgConst.cpp
	

$(CORELIB):
	(cd core;$(MAKE);cp $(CORELIB) ../$(CORELIB))
$(MODULELIB):
	(cd module;$(MAKE);cp $(MODULELIB) ../$(MODULELIB))
	
rma:
	-rm *.a
	
cleanAll:
	-rm  *.o *.a
