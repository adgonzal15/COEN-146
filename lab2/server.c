//
//  Behnam Dezfouli
//  CSEN, Santa Clara University
//

// This program implements a server that accepts connection from a client and copies the received bytes to a file
//
// The input arguments are as follows:
// argv[1]: Sever's port number

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main (int argc, char *argv[]){
	char    message[10] = "received!";  // message to be sent to the client when the destination file name is received
	int     net_bytes_read;             // numer of bytes received over socket
	int     socket_fd = 0;              // socket descriptor
	int     connection_fd = 0;          // new connection descriptor
	struct  sockaddr_in serv_addr, clien_addr; // Address format structure
	char    net_buff[1024];             // buffer to hold characters read from socket
	FILE    *dest_file;                 // pointer to the file that will include the received bytes over socket

	if (argc < 2){// Note: the name of the program is counted as an argument
		printf ("Port number not specified!\n");
		return 1;
	}
	//Socket Creation
	if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("cannot create socket\n");
		return 0;
	}
	printf("Socket Creation Successful\n");
	//Configuring Server Address
	serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((bind(socket_fd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr))) < 0){
    	perror("Failure to bind server address to the endpoint socket\n");
    	exit(1);
    }
	printf("Binding Successful\n");
	//listening
	if ((listen(socket_fd, 10)) == 0 ){
		printf("Listening\n");
	}
	else {
		perror("Listening Failed\n");
		exit(1);
	}
	//acceptance
	int size = sizeof(struct sockaddr_in);

	if ((connection_fd = accept(socket_fd, (struct sockaddr *)&clien_addr, (socklen_t *)&size)) < 0){
        perror("Failure to accept connection to the client\n");
        exit(1);
    }
	printf("Connection made\n");
	
	//Writing to dest file
	int n;
	if ((n = read(connection_fd, net_buff, sizeof(net_buff))) > 0)
    {
        dest_file = fopen(net_buff, "w");
        if (dest_file != NULL) {
            printf("Opened file successfully \n");
        }
    }
	while(1) {
		net_bytes_read = read(connection_fd,net_buff,1024);
		if (net_bytes_read < 0) {
			perror("Failure Writing");
			exit(1);
		}
		fwrite(&net_buff, net_bytes_read, 1, dest_file);
		if (net_bytes_read == 0) {
			break;
		}
	}

	return 0;
}