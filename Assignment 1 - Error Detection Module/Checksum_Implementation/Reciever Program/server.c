#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "headers/Block.h"
#include "headers/Checksum.h"


void error(const char * err){
	perror(err);
	exit(1);
}

int main(int argc, char ** argv){
	if(argc < 2){
		fprintf(stderr,"Port number is not provided... Program terminating....\n");
		exit(1);
	}
	
	int sockfd, newsockfd, portno, n;
	char buffer[255];
	
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd<0) error("Error opening Socket");

	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)))
		error("Binding Failed");

	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if(newsockfd < 0)
		error("Error on Accept");

	bzero(buffer, 255);
	n = read(newsockfd, buffer, 255);
	if(n<0) error("Error on reading");

	printf("The message received is : %s\n", buffer);
	Blockset * bs = createBlock(buffer, 16);
	printBlockset(bs);
	if(compareChecksum(bs, 16)) printf("Accepted\n");
	else printf("Rejected\n");
		
	close(newsockfd);
	close(sockfd);
	return 0;

}
