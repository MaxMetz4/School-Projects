/*******************************************************************************
 * Name        : minishell.c
 * Author      : Maxwell Metzner and Savnick Patel
 * Date        : 4/13/2021
 * Description : Learning how to make a shell program in C.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <signal.h>
#include <limits.h>
#include <sys/wait.h>


#define BRIGHTBLUE 	"\x1b[34;1m"
#define DEFAULT 	"\x1b[0m"

volatile sig_atomic_t interrupted = false;
/* Signal handler */
void catch_signal(int sig) {
	write(1,"\n",1);
	interrupted = true;
}

void print_wkdir(char* currdir) {
	//prints the current working directory (meant to precede scanf)
	printf("%s[%s%s%s]$ ",DEFAULT,BRIGHTBLUE,currdir,DEFAULT);
}

int shell(char* dir, struct passwd pwd) {
	//Create a sigaction to handle SIGINT.
	struct sigaction sa;
	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = catch_signal;
	if( (sigemptyset(&sa.sa_mask)) < 0){
		fprintf(stderr, "Error: Could not clear al signals from SET. %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}
	if (sigaction(SIGINT, &sa, NULL) < 0) {
		fprintf(stderr, "Error: Could not register signal handler. %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}
	char* currdir = dir;
	//main loop
	while(true){
		if(interrupted){
			interrupted = false;
			continue;
		}
		//display prompt
		print_wkdir(currdir);
		fflush(stdout);

		//get input
		// should improve to include cases where the input is larger than PATH_MAX
		char input[PATH_MAX];
		memset(input, 0, sizeof(input));
		ssize_t count;
		if( ( count = read(STDIN_FILENO, input, sizeof(input)) ) < 0){
			if (errno == EINTR) {
				continue;
			} else {
				fprintf(stderr, "Error: Failed to read from stdin. %s.\n", strerror(errno));
				return EXIT_FAILURE;
			}
		}
		size_t len = strlen(input);
		if( input[len-1] == '\n' ){
			input[len-1] = '\0';
		}

		//only enter
		if (strcmp(input,"") == 0) {
			continue;
		} else
		//exit
		if (strcmp(input,"exit") == 0) {
			return EXIT_SUCCESS;
		} else if ( (strcmp(input,"cd")) == 0 || (strcmp(input,"cd ~")) == 0 ) { //cd
			if( (chdir(pwd.pw_dir)) < 0){
				fprintf(stderr, "Error: Cannot change directory to '%s'. %s.\n", pwd.pw_dir, strerror(errno));
				continue;
			}
			currdir = pwd.pw_dir;
		} else if (strncmp(input,"cd ",3) == 0) {
			char *temp = input + 3;
			if ((strcmp(temp,"..") == 0)) {
				if( (chdir("..")) < 0){
					fprintf(stderr,"Error: Cannot change directory to '%s'. %s.\n", "..", strerror(errno));
					continue;
				}
				char cwd[PATH_MAX];
				if ( (currdir = getcwd(cwd, sizeof(cwd))) == NULL){
					fprintf(stderr,"Error: Cannot get current working directory. %s.\n", strerror(errno));
					return EXIT_FAILURE;
				}

			} else {
				if (strchr(temp, ' ') != NULL) {
					fprintf(stderr, "Error: Too many arguments to cd.\n");
					continue;
				}
				if ( (chdir(temp)) < 0){
					fprintf(stderr,"Error: Cannot change directory to '%s'. %s.\n", temp, strerror(errno));
					continue;
				}

				//if we are given a directory starting with / we should print out that directory
				//as it is given to us according to the sample executions
				if(input[3] == '/'){
					currdir = temp;
				} else {
					char cwd[PATH_MAX];
					if( (currdir = getcwd(cwd, sizeof(cwd))) == NULL){
						fprintf(stderr,"Error: Cannot get current working directory. %s.\n", strerror(errno));
						return EXIT_FAILURE;
					}

				}

			}
		} else {
			//exec
			//check that input is NOT #!/bin/bash (Do not exec #!/bin/bash)
			pid_t pid;
			if ((pid = fork()) < 0) {
				fprintf(stderr, "Error: fork() failed. %s.\n", strerror(errno));
				return EXIT_FAILURE;
			} else if(pid > 0){
				//parent
				int status;
				pid_t w =  wait(&status);
				if(w == -1){
					if (errno == EINTR) {
						continue;
					} else {
						fprintf(stderr, "Error: wait failed. %s.\n", strerror(errno));
						return EXIT_FAILURE;
					}
				}
			} else {
				//child
				//need a way to parse through what we were given to
				//provide the program we are execing the arguments
				//the user gave it
				char * pch;
				char *args[20];
				char *temp = input;
				pch = strtok (temp," ");
				char *argf = pch;
				int i = 0;
				while (pch != NULL) {
					args[i] = pch;
					pch = strtok (NULL, " ");
					i++;
				}

				if (execvp(argf, args) == -1) {
					fprintf(stderr, "Error: exec() failed. %s.\n", strerror(errno));
					return EXIT_FAILURE;
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 1) {
		printf("Usage: ./minishell.c\n");
		return EXIT_FAILURE;
	}
	//get the current directory in char* pwd
	uid_t id = getuid();
	struct passwd *pwd;
	errno = 0;
	if( (pwd = getpwuid(id)) == NULL){
		fprintf(stderr,"Error: Cannot get passwd entry. %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}

	char cwd[PATH_MAX];
	char *start;
	if( (start = getcwd(cwd, sizeof(cwd))) == NULL) {
		fprintf(stderr,"Error: Cannot get current working directory. %s.\n", strerror(errno));
		return EXIT_FAILURE;
	}
	return shell(start, *pwd);
}
