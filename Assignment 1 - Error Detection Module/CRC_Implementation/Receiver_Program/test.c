#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "headers/Dataword.h"
#include "headers/Generator.h"
#include "headers/CRC.h"
#include "headers/Codeword.h"


int main(){
	bool ans = (checker("1011110", "1011"));
	if( ans) printf("Accepted");
	else printf("Rejected");
}
