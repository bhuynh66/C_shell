#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct PARTITION {

    int total_blocks;
    int block_size;

} Partition;

typedef struct FAT {

    char *filename;
    int file_length;
    int blockPtrs[10];
    int current_location;

} Fat;

char * block_buffer;
FILE *fp[5];
Partition part;
Fat table[20];

void initIO(){  //initialize the global datastructures
    part.total_blocks = 0;
    part.block_size = 0;

    for(int i = 0 ; i <20 ; i++){
        table[i].filename = NULL;
        table[i].file_length = 0;
        for(int j =0 ; j < 10 ; j++){
            table[i].blockPtrs[j] = 0;
        }    
        table[i].current_location = 0;
    }

    block_buffer =NULL;
	for(int i=0; i<5 ;i++) fp[i] =NULL;

}


int partition(char *name, int blocksize, int totalblocks){

    system("mkdir PARTITION 2>/dev/null ");  //file exist then make error message go to black hole
	char names[1000];
	char *name1= (char*)malloc(sizeof(char)*1000);
	strcpy(name1, "PARTITION/");
	snprintf(names, sizeof(names), "%s.txt", name);
	strcat(name1,names);
	FILE *copy = fopen(name1 , "w+");

	if(copy==NULL) return 0; //unsucessful
	
	fprintf( copy , "%d " , totalblocks); //info from partition : total blocks
	fprintf( copy,"%d ",blocksize);	      //info from partition : blocksize
	fprintf( copy,"%s ",name);            //info from fat  : name
	fprintf(copy, "%d " , -1);            //info from fat  : blockpointer
	fprintf(copy , "%d \n" , -1);         //info from fat  : current_location

	for(int i=0;i<blocksize*totalblocks ; i++){
        
        if(i%blocksize==0) fprintf(copy,"%s", "\n"); //print zeros on a new line for clarity

        fprintf(copy, "%d" , 0); //writing the block portion of the file
                    
    }

	fclose(copy); // close file pointer

	return 1; //success

}

int mount(char *name){}

int openfile(char *name){}

int readBlock(int file){}

char *returnBlock(){}


int writeBlock(int file, char *data){}

int main(){
    

   initIO();
   
   
  /*  for(int i = 0 ; i <20 ; i++){

        printf("%s , %d, %d\n " , table[i].filename, table[i].file_length, i );
         for(int j =0 ; j < 10 ; j++){
        
            printf("%d,%d\n", table[i].blockPtrs[j], j );
        }    
        
    }
    for(int i = 0 ; i<5 ; i++) {

        printf("%p , %d \n " , fp[i], i);

    }
*/ //this blocks checks if initIO did its job; will make function later

    partition("waa",5,75);
    partition("wario",50,75);



   return 0;

}