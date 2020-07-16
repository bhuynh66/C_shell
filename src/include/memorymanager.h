struct PCB;
int launcher(FILE *p);
int countTotalPages(FILE * f);
FILE *findPage(int pageNumber, FILE *f);
int findFrame(FILE *page);
int findVictim(struct PCB *p);
int updatePageTable(struct PCB *p, int pageNumber, int frameNumber, int victimFrame);
int updateFrame(int frameNumber, int victimFrame, FILE *page);
