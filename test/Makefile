CXX = g++
CFLAGS = -I../inc -I. -g
LDFLAGS = -L../lib -lmcl

SOURCES = TestString.cpp \
	TestVector.cpp

TESTS = ${SOURCES:.cpp=.test}

.DEFAULT: all

.PHONY: all clean tests


all: test

clean:
	@rm -f *.test
	@rm -rf *.dSYM

.SUFFIXES: .cpp .test

test: ${TESTS}
	@for t in ${TESTS}; do echo -n $$t...; ./$$t; status=$$?; if [ $$status -ne 0 ]; then return $$status; else echo $$status; fi; done

.cpp.test:
	${CXX} ${CFLAGS} -o $@ $< ${LDFLAGS}
