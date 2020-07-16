#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h> 
#include "shell.h"
#include "ram.h"
#include "pcb.h"
#include "cpu.h"
#include "memorymanager.h"
#include "extern1.h"


void boot(){ //assuming backing store exist to start with
	char command[50];
	strcpy(command, "rm -rf BackingStore" );
	system(command);
	strcpy(command, "mkdir BackingStore" );
	system(command);
}

void myinit(FILE *p){

	int i=addToRAM(p); //index of page table	
	PCB* po =makePCB(p);
	po->pages_max = countTotalPages(p);
	po->PC_page= 0; //set current page table index

	for(int j=0;j<10;j++) po->pageTable[j]=-1; //-1 denotes NULL;
	po->pageTable[0]=i;
	po->PC_offset=0; 
	addToReady( po);

	FILE* fp2 = fdopen(dup (fileno (p)), "r");
	
	po->pageTable[1]=addToRAM(fp2); //load the second page into RAM;
	fseek(p,0,SEEK_SET);
	return;
}

void scheduler(){
	int count =1;
	Queue* que1 = getQueue(); //retrieve the ready list
	while(que1!=NULL && isFree()==0){	

		PCB* ready = getPCB(); //get the first instruction
		copyPC(ready->PC);   //copy it to the cpu IP
 		copyPC_offset(que1->head->PC_offset);
		FILE* new_entry=run(2);  //run program instruction with 2 quanta
		que1->head->PC_offset +=2;
		int z = que1->head->PC_offset;

		if(new_entry!=NULL){//instructions after running not null, update
			que1->head->PC_page+=1;
			int x = que1->head->PC_page;
			if(x>(que1->head->pages_max) &&z==4 ){
				RAM[que1->head->pageTable[x-1]]=NULL;
				update();  //delete head and free the node
				que1=getQueue(); 
				copyPC(NULL);				
			}		
			else if( que1->head->pageTable[x]!=-1 &&z==4){		
				fseek(RAM[que1->head->pageTable[x]],0,SEEK_SET);
				new_entry=findPage(x, RAM[que1->head->pageTable[x]]); //new file pointer
				PCB* newPCB=makePCB(new_entry);  //make pcb
				update_PCB(newPCB,que1,0,x); //copy old pcb data to new pcb
				updateFrame(x, 0, new_entry); //update frame
				updatePageTable(newPCB, x, (que1->head->pageTable[x]), 0); //update pagetable
				RAM[que1->head->pageTable[x-1]]=NULL; //set previous ram entry to NULL
				addToReady(newPCB); //add to ready
				update();   //delete head and move to next node
				que1=getQueue(); //update que1 position
				copyPC(NULL); //reset cpu IR
				
			}
			else if(que1->head->pageTable[x]==-1 &&z==4){ //not in ram but free space available		
				fseek(new_entry,0,SEEK_SET);				
				FILE* fp3 = findPage(x, new_entry); //new file pointer
				int frame = findFrame(fp3);
				if(frame!=-1){ //free space in ram
					PCB* newPCB=makePCB(fp3);  //make pcb
					update_PCB(newPCB,que1,0,x); 
					updateFrame(frame, 0, fp3); 
					updatePageTable(newPCB, x, frame, 0);
					RAM[que1->head->pageTable[x-1]]=NULL; //set previous ram entry to NULL
					addToReady(newPCB); //add to ready
					update();   //delete head and move to next node
				}

				else{ //need to find a victim	
					int id = findVictim(ready); 
					PCB* newPCB=makePCB(fp3);  //make pcb
					update_PCB(newPCB,que1,0,x); 
					updateFrame(frame, id, fp3); 
					updatePageTable(newPCB, x, frame, id);
					RAM[que1->head->pageTable[x-1]]=NULL; //set previous ram entry to NULL
					removeTableEntry(id); //update victim page table
					addToReady(newPCB); //add to ready
					update();   //delete head and move to next node
				}
				que1=getQueue(); //update que1 position			
				copyPC(NULL); //reset cpu IR
			}			
			else{//we havent page faulted yet,proceed normal
				PCB* newPCB=makePCB(new_entry);
				update_PCB(newPCB, que1 , z, x-1);  
				addToReady(newPCB);
				update();   //delete head and move to next node
				que1=getQueue(); //update que1 position
				copyPC(NULL); //reset cpu IR
			}
		}
		else {	//we get an EOF ie we ran into quit
			int x=-1;
			for(int i=0;i<10;i++){ // we want to remove any remaining pages in RAM
				x =que1->head->pageTable[i];
				if(x!=-1){
					RAM[x]=NULL;
					que1->head->pageTable[i]=-1;	
				}
			}
			if(x!=-1) fclose(RAM[x]); //close the related file
			update();  //delete head and free the node
			que1=getQueue(); 
			copyPC(NULL);
		}
	}
		return;	
}


int main(){
	boot();
	srand(time(0)); //set the seeder
	ui(); // call shell ui
	return 0;
}
