######################################################################
# @author      : HackOlympus (zeus@hackolympus)
# @file        : Makefile
# @created     : Friday Aug 05, 2022 15:42:53 IST
######################################################################

CC=gcc
CFLAGS=-Wall -fstack-protector-all

INP=$(wildcard *.c)

main: 
	$(CC) $(CFLAGS) $(INP) -o $@ 

.PHONY: clean

clean: 
	rm main
