/*******************************************************************************
 * Name        : pfind.c
 * Author      : Maxwell Metzner and Savnick Patel
 * Date        : 3/13/2021
 * Description : Find files with the specified permissions
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "permstat.h"

//tracks if there is no output
bool is_output = false;

/**
 * Displays the usage string for the program.
 */
void display_usage() {
	printf("Usage: ./pfind -d <directory> -p <permissions string> [-h]\n");
}

int dir_explorer (char* src_directory, int permissions) {
    char path[PATH_MAX];
    if (realpath(src_directory, path) == NULL) {
        is_output = true;
        fprintf(stderr, "Error: Cannot get full path of file '%s'. %s\n", src_directory, strerror(errno));
        return EXIT_FAILURE;
    }

    DIR *dir;
    if ((dir = opendir(path)) == NULL) {
        is_output = true;
    	fprintf(stderr, "Error: Cannot open directory '%s'. %s\n", path, strerror(errno));
    	return EXIT_FAILURE;
    }

    struct dirent *entry;
    struct stat sb;
    char full_filename[PATH_MAX+1];
    size_t pathlen = 0;

    // Set the initial character to the NULL byte.
    // If the path is root '/', you can now take the strlen of a properly
    // terminated empty string.
    full_filename[0] = '\0';
    if (strcmp(path, "/")) {
        // If path is not the root - '/', then ...

        // If there is no NULL byte among the first n bytes of path,
        // the full_filename will not be terminated. So, copy up to and
        // including PATH_MAX characters.
        strncpy(full_filename, path, PATH_MAX);
    }
    // Add + 1 for the trailing '/' that we're going to add.
    pathlen = strlen(full_filename) + 1;
    full_filename[pathlen - 1] = '/';
    full_filename[pathlen] = '\0';

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        strncpy(full_filename + pathlen, entry->d_name, PATH_MAX - pathlen);
        if (lstat(full_filename, &sb) < 0) {
            is_output = true;
            fprintf(stderr, "Error: Cannot stat file '%s'. %s\n",
                    full_filename, strerror(errno));
            continue;
        }
        if (entry->d_type == DT_DIR) {
        	//r
        	char *perms = get_perms(full_filename);
			if(permissionsstring_to_num(perms) == permissions){
				is_output = true;
				printf("%s\n", full_filename);
			}
			free(perms);
        	dir_explorer(full_filename, permissions);
        } else {
        	//check permissions first before
        	char *perms = get_perms(full_filename);
        	if(permissionsstring_to_num(perms) == permissions){
                is_output = true;
        		printf("%s\n", full_filename);
        	}
        	free(perms);
        }
    }

    closedir(dir);
    return EXIT_SUCCESS;
}


int main(int argc, char *argv[]) {
	if (argc == 1) {
		display_usage();
		return EXIT_FAILURE;
	}

	int opt = 0;
	int dflag = 0;
	int pflag = 0;
	char* permissions;
	char* src_file;
	opterr = 0;

	while ((opt = getopt(argc, argv, ":d:p:h")) != -1) {
		switch (opt) {
		case 'd':
			src_file = optarg;
			dflag = 1;
			break;
		case 'p':
			permissions = optarg;
			pflag = 1;
			break;
		case 'h':
			display_usage();
			return EXIT_SUCCESS;
		case '?':
			if (optopt == 'd') {
				fprintf (stderr, "Error: Option -%c requires an argument.\n", optopt);
			}
			else if (optopt == 'p') {
				fprintf (stderr, "Error: Option -%c requires an argument.\n", optopt);
			}
			else if (isprint (optopt)) {
				fprintf (stderr, "Error: Unknown option '-%c' received.\n", optopt);
			}
			else {
				fprintf (stderr, "Error: Unknown option character '\\x%x' received.\n", optopt);
			}
			return EXIT_FAILURE;
		default:
			return EXIT_FAILURE;
		}
	}

	if(dflag == 0){
		printf("Error: Required argument -d <directory> not found.\n");
		return EXIT_FAILURE;
	}

	if(pflag == 0){
		printf("Error: Required argument -p <permissions string> not found.\n");
		return EXIT_FAILURE;
	}


	struct stat sb;
	if( stat(src_file, &sb) < 0) {
		fprintf(stderr, "Error: Cannot stat '%s'. %s.\n", src_file, strerror(errno));
		return EXIT_FAILURE;
	}

	//check that the src_file is a directory
	if (!S_ISDIR(sb.st_mode)) {
		printf("Error: Directory provided is not a directory.\n");
		return EXIT_FAILURE;
	}

	size_t permlen = strlen(permissions);
	if(permlen != 9){
		fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", permissions);
		return EXIT_FAILURE;
	}
	char *t = permissions;
	for (int i = 0; i < 9; i += 3) {
		if(*t != 'r' && *t != '-'){
			fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", permissions);
			return EXIT_FAILURE;
		}
		t++;
		if(*t != 'w' && *t != '-'){
			fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", permissions);
			return EXIT_FAILURE;
		}
		t++;
		if(*t != 'x' && *t != '-'){
			fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", permissions);
			return EXIT_FAILURE;
		}
		t++;
	}
	int permissionnum = permissionsstring_to_num(permissions);

	char *perms = get_perms(src_file);
	if( permissionsstring_to_num(perms) == 0){
		printf("Error: Cannot open directory '%s'. Permission denied.\n", src_file);
		free(perms);
		return EXIT_FAILURE;
	}
	free(perms);

	int output;
	output = dir_explorer (src_file, permissionnum);
	if(output == 1){
		return EXIT_FAILURE;
	}
	if (is_output == false) {
		printf("<no output>\n");
	}
	return EXIT_SUCCESS;
}