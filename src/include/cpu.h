typedef struct CPU {
	FILE *IP;
	char IR[1000]; 
	int quanta;	
	
}CPU;

int isFree();
void copyPC(FILE *pc);
void copyPC_offset(int z);
FILE* run(int quant);
