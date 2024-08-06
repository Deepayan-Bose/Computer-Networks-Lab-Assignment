#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "Dataword.h"
// #include "Generator.h"


typedef struct codeword {
	char * c_str;
	int c_length;
}Codeword;

char xorOfString(char c1, char c2){
	if((c1=='0' && c2=='0') || (c1=='1' && c2=='1')) return '0';
	else return '1';
}
char * binary_division(char * dividend, char * divisor){
	int remainder_length = strlen(divisor)-1;
	char * remainder = (char*)calloc((remainder_length+1),sizeof(char));
	for(int i=0; i<remainder_length; i++) remainder[i] = '0';

	int n = strlen(dividend);
	//printf("N is : %d\n", n);
	for(int i=0; i<n; i++){
		char c = remainder[0];
		for ( int j=0; j<remainder_length-1; j++) {
			remainder[j] = ((divisor[j+1]=='0') ? remainder[j+1] :xorOfString(c, remainder[j+1])); 
		}

		remainder[remainder_length-1] = ((divisor[remainder_length]=='0') ? dividend[i] : xorOfString(c, dividend[i]));
		printf("Remainder is %s\n",remainder);

	}
	//printf("Remainder is : %s\n", remainder);

	char * str = (char*)malloc(strlen(dividend)*sizeof(char));
	for(int i=0; i< strlen(dividend) - strlen(divisor)+1; i++) str[i] = dividend[i];
	int j=0;
	for(int i=strlen(dividend)-strlen(divisor)+1; i<strlen(dividend); i++) str[i] = remainder[j++];

	return str;

}
Codeword * generateCodeword(Dataword * d, Generator  g){
	Codeword * c = (Codeword*)malloc(sizeof(Codeword));
	int n = d->d_length;
	int m = g.g_length;
	augmentDataword(d,m);
	
	c->c_length = n+m-1;	
	char * str = binary_division(d->d_str, g.g_str);
	c->c_str = str;
	return c;
}

void printCodeword(Codeword * c){
	printf("Codeword is :\n%s\n%d\n", c->c_str,c->c_length);
}

bool checker(char * dividend, char * divisor){
	int remainder_length = strlen(divisor)-1;
	char * remainder = (char*)calloc((remainder_length+1),sizeof(char));
	for(int i=0; i<remainder_length; i++) remainder[i] = '0';

	int n = strlen(dividend);
	//printf("N is : %d\n", n);
	for(int i=0; i<n; i++){
		char c = remainder[0];
		for ( int j=0; j<remainder_length-1; j++) {
			remainder[j] = ((divisor[j+1]=='0') ? remainder[j+1] :xorOfString(c, remainder[j+1])); 
		}

		remainder[remainder_length-1] = ((divisor[remainder_length]=='0') ? dividend[i] : xorOfString(c, dividend[i]));
		//printf("Remainder is %s\n",remainder);

	}
	//printf("Remainder is : %s\n", remainder);

	bool ans = true;

	for(int i=0; i<remainder_length; i++){
		if(remainder[i]!='0') return false;
	}
	return true;
}

