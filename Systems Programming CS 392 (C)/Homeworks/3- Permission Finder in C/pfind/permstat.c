/*******************************************************************************
 * Name        : permstat.c
 * Author      : Maxwell Metzner and Savnick Patel
 * Date        : 3/13/2021
 * Description : Return permissions of a file as a string or a number.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "permstat.h"

int perms[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};

char* get_perms(char* argv) {
	struct stat statbuf;
	if (stat(argv, &statbuf) < 0) {
		fprintf(stderr, "Error: Cannot stat '%s'. %s.\n", argv, strerror(errno));
		return NULL;
	}
	char *result = (char *)malloc(10 * sizeof(char));
	char *t = result;
	int perms[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
	int permission_valid;

	for (int i = 0; i < 9; i += 3) {
		permission_valid = statbuf.st_mode & perms[i];
		if (permission_valid) {
			*t = 'r';
			t++;
		} else {
			*t = '-';
			t++;
		}

		permission_valid = statbuf.st_mode & perms[i+1];
		if (permission_valid) {
			*t = 'w';
			t++;
		} else {
			*t = '-';
			t++;
		}

		permission_valid = statbuf.st_mode & perms[i+2];
		if (permission_valid) {
			*t = 'x';
			t++;
		} else {
			*t = '-';
			t++;
		}
	}
	*t = '\0';
	return result;
}

int permissionsstring_to_num(char* permissionstring){
	int result = 0;
	int exp = 0;
	long long num = 1;
	for(int i = 8; i>=0; --i){
		if(*permissionstring != '-') {
			for(exp = 1; exp <= i; ++exp){
				num *= 10;
			}
			result += num;
		}
		permissionstring++;
		num = 1;
	}
	return result;
}
