CC = g++
INCLUDE = .
CFLAGS = -g -Wall -ansi
SNAPSHOTLIB = snapshotlib.a

all:rma $(SNAPSHOTLIB)
$(SNAPSHOTLIB):$(SNAPSHOTLIB)(snapShotCtr.o) $(SNAPSHOTLIB)(snapShotProxy.o)

snapShotCtr.o:snapShotCtr.cpp \
	snapShotCtr.h \
	../../core/sys.h \
	../player/roleCtr.h
	$(CC) -I $(INCLUDE) $(CFLAGS) -c snapShotCtr.cpp
snapShotProxy.o:snapShotProxy.cpp \
	snapShotProxy.h \
	snapShotCtr.h \
	../../core/sys.h
	$(CC) -I $(INCLUDE) $(CFLAGS) -c snapShotProxy.cpp

rma:
	-rm *.a
	
cleanAll:
	-rm  *.o *.a
