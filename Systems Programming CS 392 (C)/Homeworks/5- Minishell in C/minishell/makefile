# * Name        : makefile
# * Author      : Maxwell Metzner and Savnick Patel
# * Date        : 4/13/2021
# * Description : Learning how to make a shell program in C.
# * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
CC     = gcc
C_FILE = $(wildcard *.c)
TARGET = $(patsubst %.c,%,$(C_FILE))
CFLAGS = -O3 -Wall -Werror -pedantic-errors -w

all:
    $(CC) $(CFLAGS) $(C_FILE) -o $(TARGET)
clean:
    rm -f $(TARGET) $(TARGET).exe