/*******************************************************************************
 * Name        : chatclient.c
 * Author      : Maxwell Metzner and Savnick Patel
 * Date        : 5/3/2021
 * Description : Practice using TCP/IP to make a chat client
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "util.h"

int client_socket = -1;
char username[MAX_NAME_LEN + 1];
char inbuf[BUFLEN + 1];
char outbuf[MAX_MSG_LEN + 1];


int handle_stdin() {
	//receive user's message from stdin
	memset(outbuf, 0, sizeof(outbuf));
	if(get_string(outbuf, sizeof(char)*(MAX_MSG_LEN + 1)) == 2){
		printf("Sorry, limit your message to %d characters.\n", MAX_MSG_LEN);
		return EXIT_SUCCESS; //not sure if we should return success or failure
	}

	//send user's message to server
	if (send(client_socket, outbuf, strlen(outbuf), 0) < 0) {
		fprintf(stderr, "Warning: Failed to send message to server. %s.\n", strerror(errno));
		//return EXIT_FAILURE;
	}

	if(strlen(outbuf)==0 || strcmp(outbuf,"\n")==0){
		return EXIT_SUCCESS;
	}

	//return 2 to exit the program in EXIT_SUCESS
	if(strcmp(outbuf,"bye") == 0){
		printf("Goodbye.\n");
		return 2;
	}

	return EXIT_SUCCESS;
}

int handle_client_socket() {
	memset(inbuf, 0, sizeof(char)*(BUFLEN + 1) );
	int bytesrec;
	bytesrec = recv(client_socket, inbuf, BUFLEN, 0); //attempt to recieve message from server
	if(bytesrec == -1) {
		fprintf(stderr, "Warning: Failed to receive incoming message. %s.\n", strerror(errno));
		return EXIT_SUCCESS;
	}
	if(bytesrec == 0){
		fprintf(stderr, "\nConnection to server has been lost.\n");
		return EXIT_FAILURE;
	}

	inbuf[bytesrec] = '\0'; //Null-terminate the string

	//return 2 to exit the program in EXIT_SUCESS
	if(strcmp(inbuf,"bye") == 0){
		printf("\nServer initiated shutdown.\n");
		return 2;
	}
	printf("\n%s\n", inbuf);

	return EXIT_SUCCESS;
}

int main(int argc, char *argv[])  {
	//wrong number of arguments provided
	if (argc != 3) {
		fprintf(stderr,"Usage: %s <server IP> <port>\n", argv[0]);
		return EXIT_FAILURE;
	}
	int retval = EXIT_SUCCESS;

	//checking the IP address is valid
	struct sockaddr_in server_addr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	memset(&server_addr, 0, addrlen);

	int ip_conversion = inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
	if (ip_conversion == 0) {
		fprintf(stderr, "Error: Invalid IP address '%s'.\n", argv[1]);
		retval = EXIT_FAILURE;
		goto EXIT;
	} else if (ip_conversion < 0) {
		fprintf(stderr, "Error: Failed to convert IP address. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
		goto EXIT;
	}

	//checking the port is valid
	int port = 0;
	const char *usage = "port number";
	if(!parse_int(argv[2], &port, usage)){
		retval = EXIT_FAILURE;
		goto EXIT;
	}
	if(port < 1024 || port > 65535){
		fprintf(stderr, "Error: Port must be in range [1024, 65535].\n");
		retval = EXIT_FAILURE;
		goto EXIT;
	}
	server_addr.sin_family = AF_INET;   // Internet address family
	server_addr.sin_port = htons(port); // Server port, 16 bits.
	// server_addr.sin_addr is already set from inet_pton() above.

	//prompting for a user
	ssize_t count;
	char buf[BUFLEN + 1]; //temp buffer to handle username input
	while(true){
		memset(buf, '\0', sizeof(char)*(BUFLEN + 1));

		printf("Enter your username: "); //print prompt
		fflush(stdout);
		count = read(STDIN_FILENO, buf, sizeof(buf));

		if(count < 0){
			fprintf(stderr, "Error: Failed to read from stdin. %s.\n", strerror(errno));
			retval = EXIT_FAILURE;
			goto EXIT;
		} else {
			size_t len = strlen(buf);
			if( buf[len-1] == '\n' ){
				buf[len-1] = '\0';
			}
			if( strlen(buf) > MAX_NAME_LEN){ //username too long
				printf("Sorry, limit your username to %d characters.\n", MAX_NAME_LEN);
			} else if( strlen(buf)==0 || strcmp(buf,"\n")==0 ){ //no usernmae provided
				//if no username is provided we loop
			} else {
				break; //valid username
			}
		}
	}

	//copy contents of buf to username array
	for(int i=0; i<strlen(buf); i++)
	{
		username[i] = buf[i];
	}

	printf("Hello, %s. Let's try to connect to the server.\n", username);

	//Establishing Connection
	// Create a stream socket using TCP.
	if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "Error: Failed to create socket. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
		goto EXIT;
	}

	//Attempt to connect to the server.
	if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in)) < 0) {
		fprintf(stderr, "Error: Failed to connect to server. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
		goto EXIT;
	}

	//receive welcome message from the server
	int bytes_recvd;
	memset(inbuf, 0, sizeof(inbuf)); // clear buffer

	if ((bytes_recvd = recv(client_socket, inbuf, BUFLEN, 0)) < 0) { //attempt to received characters
		fprintf(stderr, "Error: Failed to receive message from server. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
		goto EXIT;
	}
	if(bytes_recvd == 0){
		fprintf(stderr, "All connections are busy. Try again later.\n");
		retval = EXIT_FAILURE;
		goto EXIT;
	}
	inbuf[bytes_recvd] = '\0';
	printf("\n%s\n\n", inbuf);

	//send username to the server
	if (send(client_socket, username, strlen(username), 0) < 0) {
		fprintf(stderr, "Error: Failed to send username to server. %s.\n", strerror(errno));
		retval = EXIT_FAILURE;
		goto EXIT;
	}

	//Handing Activity on File Descriptors (Sockets)
	fd_set sockset;
	while(true){
		printf("[%s]: ", username); //print prompt
		fflush(stdout);
		// Zero out and set socket descriptors for server sockets.
		// This must be reset every time select() is called.
		FD_ZERO(&sockset);
		FD_SET(client_socket, &sockset);	//add client_socket to the fd_set
		FD_SET(STDIN_FILENO, &sockset);		//add STDIN_FILENO to the fd_set

		//select to monitor stdin and client_socket
		if (select(client_socket + 1, &sockset, NULL, NULL, NULL) < 0) {
			fprintf(stderr, "Error: select() failed. %s.\n", strerror(errno));
			retval = EXIT_FAILURE;
			goto EXIT;
		}

		// If there is activity on the STDIN_FILENO, handle the incoming
		// connection.
		if (FD_ISSET(STDIN_FILENO, &sockset)) {
			int ret1;
			ret1 = handle_stdin();
			if (ret1 == EXIT_FAILURE) {
				retval = EXIT_FAILURE;
				goto EXIT;
			}
			if(ret1 == 2){
				retval = EXIT_SUCCESS;
				goto EXIT;
			}
		}

		// If there is activity on the client socket, handle the incoming
		// connection.
		if (FD_ISSET(client_socket, &sockset)) {
			int ret2;
			ret2 = handle_client_socket();
			if (ret2 == EXIT_FAILURE) {
				retval = EXIT_FAILURE;
				goto EXIT;
			}
			if(ret2 == 2){
				retval = EXIT_SUCCESS;
				goto EXIT;
			}
		}
	}


	EXIT:
	//need to check if we have a socket open and if we do, then we need to delete it
	if (fcntl(client_socket, F_GETFD) >= 0) {
		close(client_socket);
	}
	return retval;
}
