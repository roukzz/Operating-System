
#include <stdio.h>
#include <stdlib.h>
#include "ram.h"
#include "pcb.h"
#include "kernel.h"


// "instanciate" PCB
struct PCB *makePCB(int start, int end, int pages_max){
	struct PCB *nPCB = malloc (sizeof (struct PCB));

	if (nPCB == NULL){
		printf("Error : memory allocation for new PCB could not happen");
	}
	//nPCB-> start = start;
	//nPCB->end = end;
	nPCB->pages_max = pages_max;
	nPCB->PC_offset = 0;
	nPCB->PC_page=0;
	// initialize page table when creating pcb when cell is -2 then the page has no frame associated
	for (int i = 0; i < 10; i++){
		nPCB->pageTable[i]=-2;
	}




	return nPCB;

}
// free the memory and clear the appropriate memory cells in ram
void clearPCB( struct PCB *nPCB){


	for(int i=0;i<10;i++){
	if(nPCB->pageTable[i]!=-2){

	for(int j=nPCB->pageTable[i]*4;j<(nPCB->pageTable[i]*4)+4;j++){
	//printf("clearing ram[%d]\n",j);
	ram[j]=NULL;
	}
	pcbArray[nPCB->pageTable[i]]=NULL;
	}

	free(nPCB);
	// update le pcbarrray
}
}
void clearFrame(struct PCB *thisPCB,int pageNumber){
	for(int j=thisPCB->pageTable[pageNumber]*4;j<(thisPCB->pageTable[pageNumber]*4)+4;j++){
	ram[j]=NULL;
	}

	thisPCB->pageTable[pageNumber]=-1;
	}

