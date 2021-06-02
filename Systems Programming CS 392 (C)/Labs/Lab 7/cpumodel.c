/*******************************************************************************
 * Name        : cpumodel.c
 * Author      : Maxwell Metzner and Savnick Patel
 * Date        : 3/26/2021
 * Description : Practice pfind
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool starts_with(const char *str, const char *prefix) {
	/* TODO:
	 * Return true if the string starts with prefix, false otherwise.
	 * Note that prefix might be longer than the string itself.
	 */
	while(*prefix != '\0'){
		if(str == NULL){
			return false;
		}
		if(*prefix != *str){
			return false;
		}
		str++;
		prefix++;
	}
	return true;
}

int main() {
	/* TODO:
	 * Open "cat /proc/cpuinfo" for reading, redirecting errors to /dev/null.
	 * If it fails, print the string "Error: popen() failed. %s.\n", where
	 * %s is strerror(errno) and return EXIT_FAILURE.
	 */
	FILE *fp = popen("cat /proc/cpuinfo 2>/dev/null", "r");
	if (fp == NULL) {
		fprintf(stderr, "Error: popen() failed. %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}

	/* TODO:
	 * Allocate an array of 256 characters on the stack.
	 * Use fgets to read line by line.
	 * If the line begins with "model name", print everything that comes after
	 * ": ".
	 * For example, with the line:
	 * model name      : AMD Ryzen 9 3900X 12-Core Processor
	 * print
	 * AMD Ryzen 9 3900X 12-Core Processor
	 * including the new line character.
	 * After you've printed it once, break the loop.
	 */

	char path[256];
	const char *search = "model name";
	while (fgets(path, 256, fp) != NULL) {
		if (starts_with(path, search)) {
			//print the line after index path[16] which represents the ":"
			char *p = path;
			bool colonfound = false;
			while(*p != '\0'){
				if(colonfound){
					printf("%c", *p);
				}
				if(*p == ':'){
					colonfound = true;
					p++;
				}
				p++;
			}
			break;
		}
	}

	/* TODO:
	 * Close the file descriptor and check the status.
	 * If closing the descriptor fails, print the string
	 * "Error: pclose() failed. %s.\n", where %s is strerror(errno) and return
	 * EXIT_FAILURE.
	 */
	int status = pclose(fp);
	if (status == -1) {
		fprintf(stderr, "Error: pclose() failed. %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}

	return !(WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS);
}