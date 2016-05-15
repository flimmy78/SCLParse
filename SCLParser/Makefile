
CC            = gcc
CXX           = g++

CFLAGS        = -pipe -g -D_REENTRANT  -W $(DEFINES)
CXXFLAGS      = -pipe -g -D_REENTRANT  -W $(DEFINES)
INCPATH       = -I./xercesc
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L../lib -L/usr/X11R6/lib -L/usr/lib64 -L/root/Desktop/xerces-c-3.1.3/src/.libs -L/root/Desktop/SCLParserFail/lib -lxerces-c -lSCLParser
AR            = ar cqs
RANLIB        = 
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = 
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

DESTDIR       = .
####### Output directory

#OBJECTS_DIR   = ../temp/TmpGUI/obj/

####### Files

SOURCES       = main.cpp \
		
OBJECTS       = main.o
          
INCPATH    = ./xercesc

TARGET        = TESTParser

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"


main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

#scl.o: scl.cpp scl.h Ied.h CheckNotifier.h ProgressNotifier.h SCDparse.h
#	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

#SCLParser.o:SCLParser.cpp SCLParser.h
#	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

#SclSAX2Handler.o:SclSAX2Handler.cpp SclSAX2Handler.hpp scl.h scl.cpp
#	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

#Ied.o:Ied.cpp Ied.h
#	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"



all: Makefile $(TARGET)

$(TARGET): *.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) ./lib/ || $(MKDIR) ./lib/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true





