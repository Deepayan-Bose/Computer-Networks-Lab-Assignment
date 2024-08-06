#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "headers/Block.h"
#include "headers/Checksum.h"
#include "headers/ErrorInjection.h"

void error(const char * msg){
	perror(msg);
	exit(0);
}

int main(int argc, char **argv){
	
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent * server;

	char buffer[256];
	if( argc < 3){
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(0);
	}

	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd <0) error("ERROR opening socket");

	server = gethostbyname(argv[1]);
	if(server == NULL)
	fprintf(stderr, "Error, no such host");

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("Connection failed");
	
	memset(buffer,'\0',255);
	FILE * fp = fopen("message.txt", "r");
	fscanf(fp,"%s",buffer);
	printf("The message is : %s\n",buffer);
	Blockset * bs = createBlock(buffer,16);
	printBlockset(bs);
	generateChecksum(bs,16);
	printBlockset(bs);
	memset(buffer,'\0',255);
	transferMessage(buffer, bs);
	injectError(buffer);	
	n = write(sockfd, buffer, strlen(buffer));
	if(n<0) error("Error on writing");
	close(sockfd);
	return 0;
}
