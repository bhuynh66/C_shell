INCLUDE_DIRECTORIES := src/include

VPATH = src/src

mykernel: ram.o kernel.o shell.o interpreter.o shellmemory.o pcb.o cpu.o memorymanager.o
	gcc -o mykernel ram.o kernel.o shell.o interpreter.o shellmemory.o pcb.o cpu.o memorymanager.o

ram.o: ram.c 
	gcc -c $< -I$(INCLUDE_DIRECTORIES)
	
kernel.o: kernel.c 
	gcc -c $< -I$(INCLUDE_DIRECTORIES)

shell.o: shell.c 
	gcc -c $< -I$(INCLUDE_DIRECTORIES)

interpreter.o: interpreter.c 
	gcc -c $< -I$(INCLUDE_DIRECTORIES)

shellmemory.o: shellmemory.c
	gcc -c $<
memorymanager.o: memorymanager.c
	gcc -c $< -I$(INCLUDE_DIRECTORIES)
	
pcb.o: pcb.c
	gcc -c $<

cpu.o: cpu.c 
	gcc -c $< -I$(INCLUDE_DIRECTORIES)
	
clean:
	rm -f *.o

