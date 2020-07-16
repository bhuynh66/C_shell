#include<stdio.h>
#include<string.h>
#include<stdlib.h>



typedef struct SHELLMEMORY{
	char *variable;
	char *value;
	struct SHELLMEMORY *next;	
} aNode;

aNode* head=NULL;

aNode* add(aNode* head, char *words[]){
	
	aNode* current = head;
	aNode* temp;

	if(current==NULL){//create a new node if the head is empty.
		temp= (aNode*)malloc(sizeof(aNode));
		temp->variable = words[1];
		temp->value = words[2];
		temp->next=NULL;
		return temp;	
	}
	//if initial isnt empty, check if it contains our variable
	else if(strcmp(current->variable,words[1])==0){
		current->value = words[2];
		return head;
	}
	//traverse through list to check if variable exist.
	while(current->next!=NULL){
		if(strcmp(current->variable,words[1])==0){
			current->value = words[2];
			return head;
		}
		current = current->next;
	}
	//check if the last node contains our words 
	if(strcmp(current->variable,words[1])==0){
		current->value = words[2];
		return head;
	}
	
	//if nothing is found variable doesnt exist.Add to linked list
	temp= (aNode*)malloc(sizeof(aNode));
	temp->variable = words[1];
	temp->value = words[2];
	temp->next=NULL;
	current->next=temp;
	
	return head;
}
//recursive function to check if if variable exist and print value if found.
void printl(aNode *head , char *words[]){
	if(head==NULL){
		printf("Error:Linked List is Empty \n");	
	}
	else if(strcmp(head->variable,words[1])==0){
		printf("%s \n", head->value);
	}
	else if(head->next !=NULL){
		printl(head->next , words);
	}else{
		printf("Variable does not exist \n");
	}
	return;
}

int shellmemory(char *words[],int x){
	if(x==0){
		head = add(head, words);
	}
	else if(x==1){
	  printl(head,words);
	}
	return 0;
}
