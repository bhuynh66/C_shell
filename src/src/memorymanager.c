#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include "ram.h"
#include "kernel.h"
#include "pcb.h"
#include "extern1.h"


int countTotalPages(FILE * f);
FILE *findPage(int pageNumber, FILE *f);
int findFrame(FILE *page);
int findVictim(PCB *p);
int updatePageTable(PCB *p, int pageNumber, int frameNumber, int victimFrame);
int updateFrame(int frameNumber, int victimFrame, FILE *page);
int index1=0;

int launcher(FILE *p){
	char c[1000];
	index1++;
	char name[1000];
	char *name1= (char*)malloc(sizeof(char)*1000);
	strcpy(name1, "BackingStore/");
	snprintf(name, sizeof(name), "%d.txt", index1);
	strcat(name1,name);
	int total_pages;
	FILE *copy=fopen(name1, "w+");
	//free(name1);
	if(copy==NULL) return 0;
	while(fgets(c,999,p)!=NULL){
		fputs(c,copy);
	}
	fclose(p);
	
	fseek(copy,0,SEEK_SET); //set pointer to beginning
	
	myinit(copy); //send to kernel;kernel will process
	
	
	return 1; //success	
}

int countTotalPages(FILE *f){
	int count =0;
	char temp[500];
		
	while(fgets(temp,999,f)!=NULL){
		count++; //count how many lines
	}
	if(count%4!=0){ 
		count+=(4-count%4); //round up to nearest multiple of 4
	}
	fseek(f,0,SEEK_SET);
	return count;
}

FILE *findPage(int pageNumber, FILE *fp2){
	
	char temp[500];
	for(int i=0;i<4*pageNumber; i++){
		if(fgets(temp,999,fp2)==NULL){
			return fp2; //EOF
		}
	}	
	FILE* fp3 = fdopen(dup (fileno (fp2)), "r"); //duplicate before returning
	
	return  fp2;
}

int findFrame(FILE *page){
	for(int i=0;i<10;i++){
		if(RAM[i]==NULL){
			return i;
		}
	}
	return -1;//this is full need a victim
}

int findVictim(struct PCB *p){
	int x = rand()%10;
	for(int i=0;i<10;i++){
		if(p->pageTable[i]==x){
		 (x++)%10;
		}
		else{
			break;
		}
	}
	return x; //return the victim id	
}
int updateFrame(int frameNumber, int victimFrame, FILE *page){
	if(frameNumber==-1){
		RAM[victimFrame]=page; //update ram
	}
	else{
		RAM[frameNumber]=page;	
	}	
	return 0;
}

int updatePageTable(struct PCB *p, int pageNumber, int frameNumber, int victimFrame){
	if(frameNumber==-1){
		 p->pageTable[pageNumber]= victimFrame;
		 p->pageTable[pageNumber-1]= -1; //empty previous entry
	}	
	else{
		 p->pageTable[pageNumber]= frameNumber;
		 p->pageTable[pageNumber-1]= -1; //empty previous entry
	}
	return 0;
}
