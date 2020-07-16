#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "extern1.h"

FILE* RAM[10]; //declare global ram

int addToRAM(FILE *p){
	
	for(int i=0;i<10;i++){
		if(RAM[i]==NULL){ //find first instance of empty slot and assign
			RAM[i]=p;
			return i; // return array index
		}
	}
	return -1;
}

