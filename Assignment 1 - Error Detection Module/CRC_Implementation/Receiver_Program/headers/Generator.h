#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct generator{
	char * g_str;
	int g_length;
}Generator;

Generator * createGenerator(char * str){
	Generator * g = (Generator *)malloc(sizeof(Generator));
	g->g_length = strlen(str);
	g->g_str = (char*)malloc((g->g_length+1)*sizeof(char));
	strcpy(g->g_str, str);
	return g;
}

void printGenerator(Generator *g){
	printf("Generator :\n%s\n%d\n",g->g_str, g->g_length);
}
