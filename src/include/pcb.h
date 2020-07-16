typedef struct PCB{
	FILE *PC;
	int pageTable[10];	
	int PC_page;
	int PC_offset;
	int pages_max;	
} PCB;

typedef struct READY_QUEUE{
	PCB *head;
	PCB *tail;	
}Queue;

void update_PCB(PCB* pcb, Queue* que , int offset, int page_number);
PCB* makePCB(FILE *p);
void addToReady(PCB* p);
void update();
void removeTableEntry(int id);
PCB* getPCB();
Queue* getQueue();
