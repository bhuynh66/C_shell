#include<stdio.h>
#include<string.h>
#include<stdlib.h>




typedef struct PCB{
	FILE *PC;
	int pageTable[10];	
	int PC_page;
	int PC_offset;
	int pages_max;
} PCB;

typedef struct READY_QUEUE{
	PCB *head;
	struct READY_QUEUE *tail; 
}Queue;

Queue* que = NULL;

PCB* makePCB(FILE* p ){
	PCB* pcb1 = (PCB*)malloc(sizeof(PCB));
	pcb1->PC = p;
}

void update_PCB(PCB* pcb, Queue* que , int offset, int page_number){ //helper function to copy over pcb data to new node;
	pcb->PC_offset = offset;
	pcb->PC_page = page_number;
	pcb->pages_max=que->head->pages_max;
	for(int i=0;i<10;i++){ //copy over data
		pcb->pageTable[i]=que->head->pageTable[i];
	}
	return;
}

void addToReady(PCB * p){
	Queue* current = que;
	Queue* temp = (Queue*)malloc(sizeof(Queue));
	if(current==NULL){ //node empty then add PCB
		temp->head = p;
		temp->tail=NULL;
		que = temp;
		return;
	}
	while(current->tail!=NULL){ //traverse till empty
		current = current->tail;
	}
	temp->head = p; 
	temp->tail=NULL;
	current->tail = temp;	//tail pointing to last add node
}

void update(){
	Queue* current = que;
	Queue* temp = (Queue*)malloc(sizeof(Queue));
	
	if(current==NULL){
		free(current->head->PC); //free pcb
		free(current); //free the node
	}
	temp->head = que->head;
	que = que->tail;
	free(temp); //free head node
}

void removeTableEntry(int id){ //update the victim pagetable entry
	Queue* current = que;
	while(current->tail!=NULL){  
		for(int i=0;i<10;i++){
			if(current->head->pageTable[i]==id){
				current->head->pageTable[i]=-1;
				current->head->PC_page -=1; //one page is loss
				current->head->PC_offset =0;//we lost offset as page is lost
				break;
			}
		}
		current = current->tail;
	}
	return;
}

PCB* getPCB(){//retrieve the pcb of the list
	return que->head;	
}

Queue* getQueue(){
	return que;
}
