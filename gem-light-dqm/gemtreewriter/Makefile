#
# Makefile for gemtreewriter package
#
BUILD_HOME:=$(shell pwd)/../..

CC=g++
CCFLAGS=-O2 -Wall -fPIC -pthread -m64
ADDFLAGS=-g -std=c++11
RC=rootcint
LBL=-shared -O2 -m64
LS=ls -lartF

# ROOT Config
ROOTCFLAGS=$(shell root-config --cflags)
ROOTLIBS  =$(shell root-config --libs) 
ROOTGLIBS =$(shell root-config --glibs) 

#Project=gem
Project=gem-light-dqm
Package=gemtreewriter
LongPackage=gemtreewriter
ShortPackage=treewriter
PackageName=treewriter

IncludeDirs = /usr/include/root
IncludeDirs+= $(BUILD_HOME)/$(Project)/$(Package)/include
IncludeDirs+= $(BUILD_HOME)/$(Project)/dqm-root/include
IncludeDirs+= ${BUILD_HOME}/gemdaq-testing/gemreadout/include
INC=$(IncludeDirs:%=-I%)

SRC=$(BUILD_HOME)/$(Project)/$(Package)/src/common
OBJ=$(BUILD_HOME)/$(Project)/$(Package)/src/obj
DIC=$(BUILD_HOME)/$(Project)/$(Package)/src/dic
LIB=$(BUILD_HOME)/$(Project)/$(Package)/lib/$(XDAQ_OS)/$(XDAQ_PLATFORM)
BIN=$(BUILD_HOME)/$(Project)/$(Package)/bin/$(XDAQ_OS)/$(XDAQ_PLATFORM)

Sources= Event.cxx CosmicStandEvent.cxx 
Headers= Event.h  CosmicStandEvent.h EventLinkDef.h 
Objects= $(OBJ)/Event.o $(OBJ)/EventDict.o $(OBJ)/CosmicStandEvent.o #$(OBJ)/CosmicStandEventDict.o 
#SRCDIC=$(SourceDic:%=$(BUILD_HOME)/$(Project)/$(Package)/include/%)

all:
	mkdir -p $(OBJ)
	$(CC) $(CCFLAGS) $(ROOTLIBS) $($ROOTGLIBS) $(INC) -c $(SRC)/Event.cxx -o $(OBJ)/Event.o
	$(CC) $(CCFLAGS) $(ADDFLAGS) $(ROOTLIBS) $($ROOTGLIBS) $(INC) -c $(SRC)/CosmicStandEvent.cxx -o $(OBJ)/CosmicStandEvent.o
	mkdir -p $(DIC)
	$(RC) -f $(DIC)/EventDict.cxx -c $(INC) $(Headers)
	#$(RC) -f $(DIC)/CosmicStandEventDict.cxx -c $(INC) $(Headers)
	$(CC) $(CCFLAGS) $(ROOTLIBS) $($ROOTGLIBS) $(INC) -c $(DIC)/EventDict.cxx -o $(OBJ)/EventDict.o
	#$(CC) $(CCFLAGS) $(ROOTLIBS) $($ROOTGLIBS) $(INC) -c $(DIC)/CosmicStandEventDict.cxx -o $(OBJ)/CosmicStandEventDict.o
	mkdir -p $(LIB)
	$(CC) $(LBL) $(Objects) -o $(LIB)/libEvent.so
	mkdir -p $(BIN)
	$(CC) $(ADDFLAGS) $(ROOTLIBS) $($ROOTGLIBS) $(INC) $(SRC)/gemTreeComposer.cxx $(LIB)/libEvent.so -o $(BIN)/gtc
	$(CC) $(ADDFLAGS) $(ROOTLIBS) $($ROOTGLIBS) $(INC) $(SRC)/dummyEventWriter.cxx $(LIB)/libEvent.so -o $(BIN)/dummywriter
	$(CC) $(ADDFLAGS) $(ROOTLIBS) $($ROOTGLIBS) $(INC) $(SRC)/testGeo.cxx $(LIB)/libEvent.so -o $(BIN)/testGeo
	$(LS) $(BIN)

event:
	mkdir -p $(OBJ)
	$(CC) $(CCFLAGS) $(ROOTLIBS) $($ROOTGLIBS) $(INC) -c $(SRC)/Event.cxx -o $(OBJ)/Event.o
	mkdir -p $(DIC)
	$(RC) -f $(DIC)/EventDict.cxx -c $(INC) $(Headers)
	$(CC) $(CCFLAGS) $(ROOTLIBS) $($ROOTGLIBS) $(INC) -c $(DIC)/EventDict.cxx -o $(OBJ)/EventDict.o
	mkdir -p $(LIB)
	$(CC) $(LBL) $(Objects) -o $(LIB)/libEvent.so

clean:
	rm -rf $(BIN) $(OBJ) $(DIC) $(LIB)
print-env:
	@echo BUILD_HOME    $(BUILD_HOME)
	@echo XDAQ_OS       $(XDAQ_OS)
	@echo XDAQ_PLATFORM $(XDAQ_PLATFORM)
	@echo INC           $(INC)





