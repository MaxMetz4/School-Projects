#*******************************************************************************
 # Name        : makefile
 # Author      : Maxwell Metzner and Savnick Patel
 # Date        : 3/13/2021
 # Description : makefile for pfind project
 # Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 #******************************************************************************/
pfind: pfind.o permstat.o
	gcc pfind.o permstat.o -o pfind
pfind.o: pfind.c
	gcc -g -Wall -Werror -pedantic-errors -c pfind.c
permstat.o: permstat.c permstat.h
	gcc -g -Wall -Werror -pedantic-errors -c permstat.c
clean:
	rm -f *.o pfind pfind.exe