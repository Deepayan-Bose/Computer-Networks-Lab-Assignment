#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct block{
	char * b_str;
	int b_length;
}Block;

typedef struct blockset{
	Block ** blocks;
	int number_of_blocks;
}Blockset;

Blockset* createBlock(char * msg, int block_size){
	int number_of_blocks = (int)strlen(msg)/block_size;
	if((int)strlen(msg)%block_size) number_of_blocks++;
	
	//printf("Number of blocks is : %d\n", number_of_blocks);

	Block ** blocks = (Block**) calloc(number_of_blocks, sizeof(Block*));
	//printf("Hello\n");
	for(int i=0; i<number_of_blocks; i++) blocks[i] = (Block *)calloc(block_size, sizeof(Block));
	//printf("Hello2\n");
	for(int i=0; i< number_of_blocks; i++) {
		blocks[i]->b_str = (char*)calloc(block_size,sizeof(char));
		strncpy(blocks[i]->b_str, msg+i*block_size, block_size);
		if((strlen(msg)-i*block_size) < block_size && (strlen(msg)-i*block_size)!=0){
			for(int j=strlen(msg)%block_size; j<block_size; j++) blocks[i]->b_str[j]='0';
		}
		blocks[i]->b_length = block_size;
		//printf("%s\t%d\n",blocks[i]->b_str,blocks[i]->b_length);
	}

	Blockset * bs = (Blockset*)calloc(1, sizeof(Blockset));
	bs->blocks = blocks;
	bs->number_of_blocks = number_of_blocks;

	return bs;
}

void printBlockset(Blockset * bs){
	printf("The number of blocks is %d\n",bs->number_of_blocks);
	printf("The block set is :\n");
	for(int i=0; i < bs->number_of_blocks; i++) printf("%s\t%d\n",bs->blocks[i]->b_str, bs->blocks[i]->b_length);
}

void transferMessage(char * msg, Blockset * bs){
	int number_of_blocks = bs->number_of_blocks;
	int size = bs->blocks[0]->b_length;
	for(int i=0; i< number_of_blocks; i++) strncpy(msg+i*size, bs->blocks[i]->b_str,size);
	return;
}
