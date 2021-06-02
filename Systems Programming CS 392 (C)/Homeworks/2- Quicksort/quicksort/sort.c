/*******************************************************************************
 * Name        : sort.c
 * Author      : Maxwell Metzner, Savnick Patel
 * Date        : 2/27/21
 * Description : Uses quicksort to sort a file of either ints, doubles, or
 *               strings. - "The source file that contains the main function"
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"

#include <unistd.h>

#define MAX_STRLEN     64 // Not including '\0'
#define MAX_ELEMENTS 1024

typedef enum {
	STRING,
	INT,
	DOUBLE
} elem_t;

/**
 * Basic structure of sort.c:
 *
 * Parses args with getopt.
 * Opens input file for reading.
 * Allocates space in a char** for at least MAX_ELEMENTS strings to be stored,
 * where MAX_ELEMENTS is 1024.
 * Reads in the file
 * - For each line, allocates space in each index of the char** to store the
 *   line.
 * Closes the file, after reading in all the lines.
 * Calls quicksort based on type (int, double, string) supplied on the command
 * line.
 * Frees all data.
 * Ensures there are no memory leaks with valgrind. 
 */

/**
 * Reads data from filename into an already allocated 2D array of chars.
 * Exits the entire program if the file cannot be opened.
 */
size_t read_data(char *filename, char **data) {
	// Open the file.

	FILE *fp = fopen(filename, "r");
	//"Case 3: Invalid filename -- print error message and use sterror (man 3 strerror) to provide details after the first period. Return EXIT_FAILURE"
	if (fp == NULL) {
		fprintf(stderr, "Error: Cannot open '%s'. %s. No such file or directory.\n", filename,
				strerror(errno));
		free(data);
		exit(EXIT_FAILURE);
	}

	// Read in the data.
	size_t index = 0;
	char str[MAX_STRLEN + 2];
	char *eoln;
	while (fgets(str, MAX_STRLEN + 2, fp) != NULL) {
		eoln = strchr(str, '\n');
		if (eoln == NULL) {
			str[MAX_STRLEN] = '\0';
		} else {
			*eoln = '\0';
		}
		// Ignore blank lines.
		if (strlen(str) != 0) {
			data[index] = (char *)malloc((MAX_STRLEN + 1) * sizeof(char));
			strcpy(data[index++], str);
		}
	}

	// Close the file before returning from the function.
	fclose(fp);

	return index;
}

void usage() {
	printf(	"Usage: ./sort [-i|-d] filename\n"
			"   -i: Specifies the file contains ints.\n"
			"   -d: Specifies the file contains doubles.\n"
			"   filename: The file to sort.\n"
			"   No flags defaults to sorting strings.\n");
}

int main(int argc, char **argv) {

	//Case 1: No input arguments -- print usage message and return EXIT_FAILURE.
	if (argc == 1) {
		usage();
		return EXIT_FAILURE;
	}

	int iflag = 0;
	int dflag = 0;
	int opt;
	char* filename;

	opterr = 0;

	while ((opt = getopt (argc, argv, ":id")) != -1)
		switch (opt)
		{
		case 'i':
			iflag = 1;
			break;
		case 'd':
			dflag = 1;
			break;
		case '?':
			//Case 7: Multiple Flags with Invalid Flag -- print error message for invalid flag and return EXIT_FAILURE.
			printf("Error: Unknown option '%c' received.\n",optopt);
			usage();
			return EXIT_FAILURE;
		case ':':
			//means file contains strings
			break;
		}

	if (argc - optind > 1) {
		//Case 5: Multiple filenames -- print error message and return EXIT_FAILURE.
		//multiple .txt files given
		printf("Error: Too many files specified.\n");
		return EXIT_FAILURE;

	} else if (argc-optind == 1) {
		filename = argv[optind];
	} else {
		//Case 4: No filename -- print error message and return EXIT_FAILURE.
		//no .txt file given
		printf("Error: No input file specified.\n");
		return EXIT_FAILURE;
	}

	if (iflag == 1 && dflag == 1) {
		//Case 6: Multiple Valid Flags -- print error message and return EXIT_FAILURE.
		printf("Error: Too many flags specified.\n");
		return EXIT_FAILURE;
	}

	/* GETOPTS DONE */

	char** data;
	data = (char**) calloc(MAX_ELEMENTS, sizeof(char*));
	int num_elem = read_data(filename, data);

	if (iflag == 1) {
		quicksort(data, num_elem, INT, int_cmp);
	} else if (dflag == 1) {
		quicksort(data, num_elem, DOUBLE, dbl_cmp);
	} else {
		quicksort(data, num_elem, STRING, str_cmp);
	}

	if (iflag == 1) {
		for (int i = 0; i < num_elem; i++) {
			printf("%i\n", atoi( *(data + i) ));
		}
	} else if (dflag == 1) {
		for (int i = 0; i < num_elem; i++) {
			printf("%f\n", atof( *(data + i) ));
		}
	} else {
		for (int i = 0; i < num_elem; i++) {
			printf("%s\n", *(data + i));
		}
	}
	for (int i = 0; i < num_elem; i++) {
		free(data[i]);
	}
	free(data);
	return EXIT_SUCCESS;
}
