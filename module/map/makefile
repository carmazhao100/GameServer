CC = g++
INCLUDE = .
CFLAGS = -g -Wall -ansi
MAPLIB = maplib.a

all:rma $(MAPLIB)
$(MAPLIB):$(MAPLIB)(mapCtr.o) $(MAPLIB)(mapCtrMediator.o) $(MAPLIB)(mapCtrProxy.o) $(MAPLIB)(mapUtil.o)

mapCtr.o:mapCtr.cpp \
	mapCtr.h \
	../../core/sys.h 
	$(CC) -I $(INCLUDE) $(CFLAGS) -c mapCtr.cpp
mapCtrMediator.o:mapCtrMediator.cpp \
		mapCtrMediator.h \
		../../core/sys.h
	$(CC) -I $(INCLUDE) $(CFLAGS) -c mapCtrMediator.cpp
mapCtrProxy.o:mapCtrProxy.cpp \
		mapCtrProxy.h \
		../../core/sys.h
	$(CC) -I $(INCLUDE) $(CFLAGS) -c mapCtrProxy.cpp
mapUtil.o:mapUtil.cpp \
		mapUtil.h \
		mapCtr.h \
		../../core/sys.h
	$(CC) -I $(INCLUDE) $(CFLAGS) -c mapUtil.cpp

rma:
	-rm *.a
	
cleanAll:
	-rm  *.o *.a
