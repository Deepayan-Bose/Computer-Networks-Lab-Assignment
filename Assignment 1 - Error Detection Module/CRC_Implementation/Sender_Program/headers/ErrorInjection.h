

void flipBit(char * c, int position){
	if(c[position]=='0') c[position]='1';
	else c[position]='0';	
}
void injectError(Codeword *c){
	int n = c->c_length;
	
	srand(time(0));

	int errorNumbers = (rand()%n);

	while(errorNumbers){
		int position = rand()%n;
		flipBit(c->c_str, position);
		errorNumbers--;	
	}


}
