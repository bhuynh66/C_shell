#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include "interpreter.h"


int parse(char input[]);

int ui(){
	printf("Kernel 3.0 loaded!\n");
	printf("Welcome to the Sea shell!\n");
	printf("Version 4.0 Updated June 2020 \n");
	
	char prompt[100] = {'$', '\0'};
	char input[1000];
	
	//take inputs then pass it to the parser.
	
	while(1){
		printf("%s", prompt);
		if(fgets(input,999,stdin)!=NULL){
			int x = parse(input);
			if(x==99){
				char command[50];
				strcpy(command, "rm -rf BackingStore " );
				system(command);
				sleep(2);
				exit(0);
			}
		}
		else{
			printf("\n");
			freopen("/dev/tty", "r", stdin);
		}	
	}
	return 0;
}

int parse(char input[]){
	int i;
	int j=0;
	int w =0;
	char tmp[200];
	char *words[1000];
	
	for(i=0;i<1000;i++){
		//'\0' then at end of sentence, copy word into words array
		
		if(input[i]== '\0'){
			tmp[j-1]=input[i];
			words[w]=strdup(tmp);
			w++;
			break;
		}
		//add word to tmp, if it isnt a space		
		if(input[i] != ' ' && input[i] != '\r'){
			tmp[j] = input[i];
			j++;
		}
		//if there are alot of spaces inbetween (e.g set           x      p)
		// copy word into word array and proceed. 
		else if (input[i]== ' ' && input[i+1] != ' '){
			tmp[j]='\0';
			words[w]=strdup(tmp);
			w++;
			j=0;
		}
	}
	//add '\0' to the next slot of words[] for indexing purposes.
	tmp[0]='\0';
	words[w]=strdup(tmp);
	
	return interpreter(words);	
}
