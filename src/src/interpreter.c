#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "shellmemory.h"
#include "shell.h"
#include "ram.h"
#include "kernel.h"
#include "memorymanager.h"



//checks if number of arguments are met
int valid(char *words[],int x, int n){
	if(strcmp(words[x],"\0")==0){
		return n;
	}
	valid(words,x+1,n+1);	
}
//check if we have valid extension.
int valid_ex(char words[]){
	char ext[100];
	char *extension[1000]={""};
	int val =0;
	int j=1;
	for(int i=0; i< 100 ;i++){
		if(words[i]=='.'){
			ext[0]=words[i];
			for(int w=(i+1);w<100;w++){
				if(words[w]=='\0'){
					ext[j]='\0';
					break;
				}
				ext[j]=words[w];
				j++;
			}
		}
		if(j>=3){
			extension[0]=strdup(ext);
			val = strcmp(extension[0],".txt");
			return val;
		}
		if(words[i]=='\0'){ //we couldnt find the correct extension
			break;
		}			
	}
	return -1;	
}

int help(char *words[]){
	if(valid(words,1,0)==0){
		printf("COMMAND                      DESCRIPTION \n");
		printf("\n");
		printf("help                         Displays all the commands \n");
		printf("quit                         Exits/terminates the shell with \"Bye!\" \n");
		printf("set VAR STRING               Assigns a value to shell memory \n");
		printf("print VAR                    Prints the STRING assigned to VAR \n");
		printf("run SCRIPT.TXT               Executes the file SCRIPT.TXT \n");
		printf("exec p1 p2 p3                Executes concurrent programs\n");
		printf("                             $ exec prog.txt prog2.txt\n");
		printf("\n");
	}
	else{
		printf("Error: The syntax of the command is incorrect.\n");
	}
	return 0;	
}

int quit(char *words[]){
	int errorCode=0;
	if(valid(words,1,0)==0){
		printf("Bye!\n");
		errorCode=99;
	}
	else{
		printf("Error: The syntax of the command is incorrect.\n");
	}
	return errorCode;
}

int set(char *words[]){
	int errorCode=0;
	if(valid(words,1,0)>=2){ //check if variables exist
		
		char *string=(char*)malloc(1000);
		strcpy(string,"");
		for(int i=2;i<1000;i++){
			if(strcmp(words[i],"\0")==0){
				break;
			}
			strcat(string,words[i]);
			strcat(string," ");	
		}
		strcpy(words[2],"");
		strcpy(words[2],string);
		free(string);

		errorCode= shellmemory(words,0);
		printf("\n");

	}else{
		printf("Error: The syntax of the command is incorrect.\n");
	}
	return errorCode;
}

int print(char *words[]){
	if(valid(words,1,0)==1){ //check if variable exist	
		return shellmemory(words,1);
	}
	else{
		printf("Error: The syntax of the command is incorrect.\n");
	}
	return 0;
}

int script(char *words[]){
	int errorCode=0;
	if(valid(words,1,0)==1&&valid_ex(words[1])==0){ //check if there is an argument(script) and if it has right extension
			
		char line[1000];	
		FILE *ptr =fopen(words[1], "r");
	
		if(ptr==NULL){
			printf("Error: Script not found. \n");
			return errorCode;
		}
	
		while(fgets(line,999,ptr)!=NULL){
			errorCode= parse(line);
			if(errorCode !=0){
				return errorCode;
			}	
		}	
		fclose(ptr);
	}
	else{
		printf("Error: The syntax of the command is incorrect.\n");
	}
	return errorCode;
}


int exec(char *words[]){
	int errCode=0;
	int success = 0; //launch sucess number
	int dup=0; //progs in ram?
	int args_progs = valid(words,1,0); //number of allowed args
	
	if(args_progs>=1 && args_progs <=3){
		for(int i =1; i<=args_progs ; i++){
	
			if(valid_ex(words[i])!=0){
				printf("Error: The syntax of the command is incorrect.\n");
				return errCode;
			}
		}
		   
		for(int i=1; i<=args_progs;i++){//we loading same files? print error
			
			FILE* filea = fopen(words[i],"r");	
			if(filea!= NULL){ //run launcher
				dup+=launcher(filea); //call the launcher
			}
			else{
				printf("Error: Script not found. \n");
			}
		}
		if(dup>0){ // program loaded ? call scheduler
			scheduler();	
		}
		else{
			printf("Error: No program loaded into RAM. \n");
		}
	}
	else{
		printf("Error: The syntax of the command is incorrect.\n");
	}
	return 0;	
}

int interpreter(char *words[]){
	int errCode=0;
	if(strcmp(words[0],"help")==0){
		errCode= help(words);		
	}
	else if(strcmp(words[0],"quit")==0){
		errCode= quit(words);	
	}
	else if(strcmp(words[0],"set")==0){
		errCode = set(words);
	}
	else if(strcmp(words[0],"print")==0){
		errCode= print(words);
	}
	else if(strcmp(words[0],"run")==0){
		errCode= script(words);
	}
	else if(strcmp(words[0],"exec")==0){
		errCode= exec(words);
	}
	else{
	printf("Unknown command. \n");
	}
	return errCode;
}
