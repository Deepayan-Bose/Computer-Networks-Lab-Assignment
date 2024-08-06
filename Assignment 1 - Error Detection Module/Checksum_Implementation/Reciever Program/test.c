#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "headers/Block.h"
#include "headers/Checksum.h"
int main(){
	FILE *fp = fopen("message.txt","r");
	char buffer[255];
	memset(buffer,'\0',255);
	fscanf(fp,"%s", buffer);
	printf("The message is %s\n", buffer);
	Blockset * bs = createBlock(buffer, 16);
	printBlockset(bs);
	if(compareChecksum(bs, 16)) printf("Accepted\n");
	else printf("Rejected\n");

	//printBlockset(bs);
	//memset(buffer,'\0',255);
	//transferMessage(buffer, bs);
	//printf("The message to be passed is : %s\n", buffer);
}
