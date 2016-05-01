CC=g++
CFLAGS=-c -Wall -std=c++11

all: asmblr

lexer: lexer.h lexer.cpp
	 $(CC) $(CFLAGS) lexer.cpp

parser: parser.cpp
	$(CC) $(CFLAGS) parser.cpp

translator: translator.cpp
	$(CC) $(CFLAGS) translator.cpp

asmblr: lexer.o parser.o translator.o
	$(CC) lexer.o parser.o translator.o -o asmblr.o
