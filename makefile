# 
# This will be the makefile for R2TK
#
# Once any new files are added to the toolkit, new rules for building them should also
# be provided.
#
# CC = the compiler to use
# CFLAGS = the compiler flags
# SOURCE_FILES = all the source files. Should any new be added, add these to this line.
# OBJECT_FILES = all the object files, auto-generated.
#
CC = g++
CFLAGS = -Wall

SOURCE_FILES = r2-exception.cpp r2-assert.cpp r2-math.cpp r2-argument-parser.cpp r2-data-types.cpp r2-serialize.cpp
OBJECT_FILES = $(SOURCE_FILES:.cpp=.o)



all: libr2tk.a

test: libr2tk.a test-main.cpp
	rm -f $@
	g++ -o $@ *.cpp -L. -lr2tk

clean:
	rm -f test
	rm -f libr2tk.a
	rm -f *.o

install: libr2tk.a
	mv libr2tk.a /usr/lib

uninstall:
	rm -f /usr/lib/libr2tk.a




libr2tk.a: $(OBJECT_FILES)
	rm -f $@
	ar cq $@ $(OBJECT_FILES)