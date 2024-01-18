CC  = gcc
CXX = g++
#CXX = clang
FC  = gfortran

CFLAGS := $(CFLAGS) -O2 -Wall -v -fPIC -std=gnu++0x
FFLAGS := $(FFLAGS) -fPIC

#List where source file locations here
VPATH=src

IFLAGS := $(IFLAGS) -I. -I./include
LFLAGS := $(MYLIBS) $(LFLAGS)

#[target]: [targets this target depends on, make processes them first]
#Running "make" equals "make all" by default
all: main.o ProgClass.o
	$(CXX) -o exe main.o lib/ProgClass.o

main.o: main.cxx ProgClass.o
	$(CXX) $(CFLAGS) $(IFLAGS) -c main.cxx

ProgClass.o:
	cd src \
	&& $(CXX) $(CFLAGS) -I../include  $(IFLAGS) -c ProgClass.cxx \
	&& mv ProgClass.o ../lib

clean:
	rm exe *.o lib/*.o
