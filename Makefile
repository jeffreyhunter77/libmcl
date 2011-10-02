CXX = g++
CFLAGS = -Iinc -I. 
AR = ar
DIRS = lib
VPATH = src

OBJECTS = src/error_messages.o \
	src/hash_functions.o \
	src/String.o

.DEFAULT: all

.PHONY: all clean test dirs


all: lib/libmcl.a

dirs:
	@for d in ${DIRS}; do if [ ! -d $$d ]; then mkdir $$d; fi; done

clean:
	@rm -f src/*.o
	@rm -rf ${DIRS}
	@rm -f test/*.test

test:	lib/libmcl.a
	${MAKE} -C test ${.MAKEFLAGS}

.SUFFIXES: .cpp .o

.PATH: src

lib/libmcl.a: dirs ${OBJECTS}
	${AR} rcs $@ ${OBJECTS}

.cpp.o:
	${CXX} ${CFLAGS} -c -o $@ $<
