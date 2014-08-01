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
MODULELIB = modulelib.a
#定义库的名字们
PLAYERLIB = playerlib.a
MAPLIB	  = maplib.a
SNAPSHOTLIB = snapshotlib.a
#定义目标的依赖
OBJS =
LIBS = $(PLAYERLIB) $(MAPLIB) $(SNAPSHOTLIB)


include tool.mk

all:rma $(MODULELIB)

$(MODULELIB):$(LIBS) $(OBJS)
	$(BUILD_LIBRARY)

$(PLAYERLIB):
	(cd player;$(MAKE);cp $(PLAYERLIB) ../$(PLAYERLIB))
$(MAPLIB):
	(cd map;$(MAKE);cp $(MAPLIB) ../$(MAPLIB))
$(SNAPSHOTLIB):
	(cd snapShot;$(MAKE);cp $(SNAPSHOTLIB) ../$(SNAPSHOTLIB))
	
rma:
	-rm *.a
	
clean:
	-rm $(LIBS) $(OBJS)
