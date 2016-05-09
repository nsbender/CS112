# Makefile for OpenMP lab exercise
#  by Joel Adams, for CS 112 at Calvin College
#  Spring 2009.

OBJS=runTimeTrials tester
CC=g++
CFLAGS=-c -Wall -fopenmp
LFLAGS=-fopenmp

all: $(OBJS) 

runTimeTrials: runTimeTrials.o Matrix.o 
	@echo  'Linking target: $@'
	$(CC) runTimeTrials.o Matrix.o -o runTimeTrials $(LFLAGS)
	@echo  'Finished building target: $@'
	@echo ' '

runTimeTrials.o: runTimeTrials.cpp MatrixTimer.h Matrix.h
	@echo  'Compiling: $<'
	$(CC) $(CFLAGS) runTimeTrials.cpp
	@echo ' '
	
tester: tester.o MatrixTester.o Matrix.o 
	@echo  'Linking target: $@'
	$(CC) tester.o MatrixTester.o Matrix.o -o tester $(LFLAGS)
	@echo  'Finished building target: $@'
	@echo ' '

tester.o: tester.cpp MatrixTester.h
	@echo  'Compiling: $<'
	$(CC) $(CFLAGS) tester.cpp
	@echo ' '

MatrixTester.o: MatrixTester.cpp MatrixTester.h
	@echo  'Compiling: $<'
	$(CC) $(CFLAGS) MatrixTester.cpp
	@echo ' '

Matrix.o: Matrix.cpp Matrix.h
	@echo  'Compiling: $<'
	$(CC) $(CFLAGS) Matrix.cpp
	@echo ' '
	
MatrixTester.h: Matrix.h
MatrixTimer.h: Matrix.h

clean:
	rm -f $(OBJS) a.out *~ *# *.o

