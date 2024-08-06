#include <math.h>
#include <stdlib.h>
#include <string.h>

void injectError( char * msg){
	int n = strlen(msg);
	int count = rand()%n;
	while(count--){
		int i = rand()%n;
		msg[i] = (msg[i]=='0') ? '1' : '0';
	}
}
