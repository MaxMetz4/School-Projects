/*******************************************************************************
 * Name        : spfind.c
 * Author      : Maxwell Metzner and Savnick Patel
 * Date        : 3/31/2021
 * Description : Find files with the specified permissions and sort them.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include<sys/types.h>
#include <stdbool.h>

/**
 * Displays the usage string for the program.
 */
void display_usage() {
	printf("Usage: ./spfind -d <directory> -p <permissions string> [-h]\n");
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		display_usage();
		return EXIT_FAILURE;
	}

	//get the arguments and make sure the flags are correct
	int opt = 0;
	int dflag = 0;
	int pflag = 0;
	char* permissions;
	char* src_dirc;
	opterr = 0;

	while ((opt = getopt(argc, argv, ":d:p:h")) != -1) {
		switch (opt) {
		case 'd':
			src_dirc = optarg;
			dflag = 1;
			break;
		case 'p':
			permissions = optarg;
			pflag = 1;
			break;
		case 'h':
			display_usage();
			return EXIT_SUCCESS;
		case ':':
			if(dflag == 0) {
				fprintf (stderr,"Error: Required argument -d <directory> not found.\n");
			}
			else if(pflag == 0) {
				fprintf (stderr, "Error: Required argument -p <permissions string> not found.\n");
			}
			return EXIT_FAILURE;
		case '?':
			fprintf (stderr, "Error: Unknown option '-%c' received.\n", optopt);
			return EXIT_FAILURE;
		}
	}

	//check if the d or p flag is missing
	if(dflag == 0){
		printf("Error: Required argument -d <directory> not found.\n");
		return EXIT_FAILURE;
	}

	if(pflag == 0){
		printf("Error: Required argument -p <permissions string> not found.\n");
		return EXIT_FAILURE;
	}

	//set up pipes from pfind_to_sort and sort_to_parent
	int pfind_to_sort[2], sort_to_parent[2];
	if(pipe(pfind_to_sort) < 0){
		fprintf(stderr, "Error: Cannot create pipe pfind_to_sort. %s.\n",
				strerror(errno));
		return EXIT_FAILURE;
	}
	if(pipe(sort_to_parent) < 0){
		fprintf(stderr, "Error: Cannot create pipe sort_to_parent. %s.\n",
				strerror(errno));
		return EXIT_FAILURE;
	}

	pid_t pid[2];
	if ((pid[0] = fork()) == 0) {
		// pfind
		close(pfind_to_sort[0]);
		if(dup2(pfind_to_sort[1], STDOUT_FILENO) < 0){
			fprintf(stderr, "Error: Failed to dup2. %s.\n", strerror(errno));
			close(pfind_to_sort[1]);
			close(sort_to_parent[1]);
			close(sort_to_parent[0]);
			exit(EXIT_FAILURE);
		}

		// Close all unrelated file descriptors.
		close(sort_to_parent[1]);
		close(sort_to_parent[0]);


		const char *d = src_dirc;
		const char *p = permissions;
		//need to get the source directory and permissionstr using getopts
		//need to check for specific output for failures when exec-ing ‘pfind’
		if (execl("pfind", "pfind", "-d", d, "-p", p, NULL) < 0){
			fprintf(stderr, "Error: pfind failed. %s.\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	if(pid[0] < 0){
		fprintf(stderr, "Error: fork() failed. %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}

	if ((pid[1] = fork()) == 0) {
		// sort
		close(pfind_to_sort[1]);
		if(dup2(pfind_to_sort[0], STDIN_FILENO) < 0){
			fprintf(stderr, "Error: Failed to dup2. %s.\n", strerror(errno));
			close(pfind_to_sort[0]);
			close(sort_to_parent[1]);
			close(sort_to_parent[0]);
			exit(EXIT_FAILURE);
		}

		close(sort_to_parent[0]);
		if(dup2(sort_to_parent[1], STDOUT_FILENO) < 0){
			fprintf(stderr, "Error: Failed to dup2. %s.\n", strerror(errno));
			close(sort_to_parent[1]);
			close(pfind_to_sort[0]);
			exit(EXIT_FAILURE);
		}

		//need to check for specific output for failures when exec-ing ‘sort’
		if (execlp("sort", "sort", NULL) < 0){
			fprintf(stderr, "Error: sort failed. %s.\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	if(pid[1] < 0){
		fprintf(stderr, "Error: fork() failed. %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}

	close(sort_to_parent[1]);
	if(dup2(sort_to_parent[0], STDIN_FILENO) < 0){
		fprintf(stderr, "Error: Failed to dup2. %s.\n", strerror(errno));
		close(sort_to_parent[0]);
		close(pfind_to_sort[1]);
		close(pfind_to_sort[0]);
		exit(EXIT_FAILURE);
	}
	// Close all unrelated file descriptors.
	close(pfind_to_sort[1]);
	close(pfind_to_sort[0]);

	int numOfMatches = 0;
	char buffer[4096];
	while (1) {
		ssize_t count = read(STDIN_FILENO, buffer, sizeof(buffer));
		if (count < 0) {
			if (errno == EINTR) {
				continue;
			}
			else {
				fprintf(stderr, "Error: read failed. %s.\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
		} else if (count == 0) {
			break;
		} else {
			//parse through the buffer checking for \n to determine
			//how many lines were returned
			char *t = buffer;
			for(int i = 0; i < count; i++){
				if(*t == '\n'){
					++numOfMatches;
				}
				t++;
			}

			if(write(STDOUT_FILENO, buffer, count) < 0){
				fprintf(stderr, "Error: write failed. %s.\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
		}
	}

	close(sort_to_parent[0]);

	//wait for child 1
	int status1;
	int es1;
	pid_t w =  wait(&status1);
	if(w == -1){
		fprintf(stderr, "Error: wait failed. %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if( WIFEXITED(status1) ){
		es1 = WEXITSTATUS(status1);
	}

	//wait for child 2
	int status2;
	int es2;
	pid_t w2 =  wait(&status2);
	if(w2 == -1){
		fprintf(stderr, "Error: wait failed. %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if( WIFEXITED(status2) ){
		es2 = WEXITSTATUS(status2);
	}

	if(es1 != 1 && es2 != 1){
		//need to print out how many lines were returned
		printf("Total matches: %i\n", numOfMatches);
	}

	return EXIT_SUCCESS;
}
