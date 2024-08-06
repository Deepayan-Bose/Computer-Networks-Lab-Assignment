#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct checksum{
	char * c_str;
	int c_length;
}Checksum;

Checksum * initializeChecksum(int block_size){
	Checksum * c = (Checksum *)calloc(1, sizeof(Checksum));
	c->c_str = (char*)calloc(block_size, sizeof(char));
	c->c_length = block_size;
	memset(c->c_str,'0',c->c_length);
	return c;
}

void generateChecksum(Blockset * bs, int block_size){
	Checksum * c = initializeChecksum(block_size);
	int number_of_blocks = bs->number_of_blocks;
	for(int i=0; i<number_of_blocks; i++){
		int carry = 0;
		for (int j= block_size-1; j>=0; j--){
			int number_of_ones = (c->c_str[j]=='1') + (bs->blocks[i]->b_str[j]=='1') + carry;
			carry = number_of_ones/2;
			c->c_str[j] = (number_of_ones%2) ? '1' : '0';	
		}
		//printf("Checksum is \t%s\n", c->c_str);
	
		if(carry){
			int j = block_size-1;
			while(carry){
				int number_of_ones = (c->c_str[j]=='1') + carry;
				carry = number_of_ones/2;
				c->c_str[j] = (number_of_ones%2) ? '1' : '0';
				j--;	
			}
		}
		//printf("Checksum is \t%s\n", c->c_str);
	}
	printf("Checksum is \t%s\n", c->c_str);
	for(int i=0; i<block_size; i++) c->c_str[i] = (c->c_str[i]=='0') ? '1' : '0';
	printf("Complemented checksum is \t%s\n", c->c_str);
	bs->blocks = (Block **) realloc(bs->blocks, (number_of_blocks+1)*sizeof(Block*));
	bs->blocks[number_of_blocks] = (Block *) calloc(1, sizeof(Block));
	bs->number_of_blocks++;
	number_of_blocks++;

	bs->blocks[number_of_blocks-1]->b_str = (char*)calloc(block_size+1, sizeof(char));

	strcpy(bs->blocks[number_of_blocks-1]->b_str, c->c_str);

	bs->blocks[number_of_blocks-1]->b_length = block_size;

}
