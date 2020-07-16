#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "shell.h"

typedef struct CPU {
	FILE *IP;
	char IR[1000]; 
	int quanta;
	int offset;
	
}CPU;

CPU cpu={NULL,'\0',0,0};

int isFree(){ //we check if quanta is  0 or IP is free
	if(cpu.IP==NULL || cpu.quanta==0){
		return 0;
	}
	return -1;
}

void copyPC(FILE *pc){	
	cpu.IP= pc;	
}
void copyPC_offset(int z){	
	cpu.offset= z;	
}

FILE* run(int quant){
	cpu.quanta=quant; //set cpu quanta
	while(cpu.quanta!=0 && fgets(cpu.IR,999,cpu.IP) !=NULL){
	
		if(parse(cpu.IR)==99){ //run program && check for quit
			
			fseek(cpu.IP,0,SEEK_END); //set to end of file
			return NULL;
		}

		if(cpu.offset==4){
			return cpu.IP;
		}	
		
		cpu.quanta -=1;
		cpu.offset+=1;
	}
	
	
	return cpu.IP; //return the intruction location
}
