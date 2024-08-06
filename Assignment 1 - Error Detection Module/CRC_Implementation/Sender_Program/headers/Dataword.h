#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct dataword {
	char * d_str;
	int d_length;
}Dataword;

Dataword* createDataword(char * str){
	Dataword* d = (Dataword *)malloc(sizeof(Dataword));
	d->d_length = strlen(str);
	d->d_str = (char*)malloc((d->d_length+1)*sizeof(char));
	strcpy(d->d_str, str);
	return d;
}

void printDataword(Dataword * d){
	printf("The dataword is :\n%s\n%d\n", d->d_str, d->d_length);
}

void augmentDataword(Dataword * d, int m){
	char * augmentedPart = (char*)calloc((m),sizeof(char));
	for(int i=0; i<m-1; i++) augmentedPart[i]='0';
	d->d_str = (char*) realloc(d->d_str,(d->d_length+m)*sizeof(char));
	strcat(d->d_str, augmentedPart);
	d->d_length = d->d_length+m-1;
	//printf("Augmented Dataword is %s\nLength is %d\n", d->d_str, d->d_length);

}
