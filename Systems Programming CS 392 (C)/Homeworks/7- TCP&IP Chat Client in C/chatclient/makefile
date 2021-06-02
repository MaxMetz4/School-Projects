#Name        : makefile
#Author      : Maxwell Metzner and Savnick Patel
#Date        : 5/3/2021
#Description : makefile for chatclient
#Pledge : I pledge my honor that I have abided by the Stevens Honor System.

CC     = gcc
C_FILE = $(wildcard *.c)
TARGET = $(patsubst %.c,%,$(C_FILE))
CFLAGS = -g -Wall -Werror -pedantic-errors

all:
	$(CC) $(CFLAGS) $(C_FILE) -o $(TARGET)
clean:
	rm -f $(TARGET) $(TARGET).exe
