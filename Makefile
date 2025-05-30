###
### Makefile for CalcYouLater Project
### CalcYouLater is an RPN calculator
###
### Author:  YOUR NAME HERE

# this is needed to have make follow symlinks in dependency lists -- please keep
# it! (but remove this comment)
MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

RPNCalc.o: RPNCalc.cpp RPNCalc.h

DatumStack.o: DatumStack.cpp DatumStack.h Datum.h

parser.o: parser.cpp parser.h

main.o: main.cpp Datum.h DatumStack.h parser.h RPNCalc.h

# CalcYouLater.o: main.cpp Datum.h DatumStack.h parser.h RPNCalc.h

CalcYouLater: main.o parser.o DatumStack.o Datum.o RPNCalc.o
	${CXX} ${LDFLAGS} -o $@ $^

## Rules for building an executable from Datum+vector_example.cpp
## This is useful in seeing the behavior of Datum::toString()
Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^

unit_test: unit_test_driver.o Datum.o DatumStack.o parser.o
	$(CXX) $(CXXFLAGS) $^
##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
