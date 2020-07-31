# C_shell

This was a project for "COMP310: Operating systems".

Run on Ubuntu.

In the terminal, run the program as:

    ./mykernel
 
 When the program starts, type in the terminal "help" and it will display the list of supported commands.
 
 The txt file provided are the "programs" that this shell supports.
 
 Otherwise one can run the program from terminal as follows:
 
     ./mykernel < test_main.txt
   
## Page faulting and Task switch

Given our program, every two line of instruction counts as a quanta. We introduce an offset to count the number of quanta.
When the offset reaches 4, we generate a pseudo interrupt. We stop the current program execution and check for the next "page" in the pageTable. If it exist then we can retrieve it from ram and reset the offset to 0. Otherwise, we find the page in the backingstore. Then find space in the ram (if no space exist then we need to find a victim) , update the pagetables, reset offset to 0, and grab our new page from ram.
     


    
    
     
