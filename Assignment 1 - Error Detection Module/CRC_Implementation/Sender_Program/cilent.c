#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include "headers/Dataword.h"
#include "headers/Generator.h"
#include "headers/CRC.h"
#include "headers/Codeword.h"
#include "headers/ErrorInjection.h"
void error(const char * msg){
	perror(msg);
	exit(0);
}
int main(int argc, char ** argv){
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent * server;

	char buffer[255];

	if(argc < 3){
		fprintf(stderr, "Did not enter the arguments correctly");
		exit(0);
	}

	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) error("Error opening socket");

	server = gethostbyname(argv[1]);
	if(server == NULL) fprintf(stderr, "Error, no such host");

	bzero((char*) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	bcopy((char*) server->h_addr, (char*) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ) error("Connection failed");

	FILE * fp = fopen("message.txt", "r");
	char * message= (char*) malloc(255*sizeof(char));
       	fscanf(fp,"%s", message);
	printf("The message receieved is : %s\n", message);
	memset(buffer,'\0',255*sizeof(char));

	strcpy(buffer,message);
	printf("Buffer is %s\n",buffer);
	Dataword * d = createDataword(message);
	printDataword(d);
	Generator  g = {"1011",4};
       	Codeword * c = generateCodeword(d, g);
	printCodeword(c);
	injectError(c);
	printf("After injecting error :");
	printCodeword(c);
	strcpy(buffer, c->c_str);
		
	n= write(sockfd, buffer, strlen(buffer));
	if (n<0) error("Error while writing");
	
	close(sockfd);
	return 0;
}
