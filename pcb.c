
#include <stdio.h>
#include <stdlib.h>
#include "ram.h"
#include "pcb.h"


// "instanciate" PCB
struct PCB *makePCB(int start, int end){
	struct PCB *nPCB = malloc (sizeof (struct PCB));

	if (nPCB == NULL){
		printf("Error : memory allocation for new PCB could not happen");
	}
	nPCB-> start = start;
	nPCB->end = end;
	nPCB->PC = start;

	return nPCB;

}
// free the memory and clear the appropriate memory cells in ram
void clearPCB( struct PCB *nPCB){
	emptyRam(nPCB->start, nPCB->end);
	free(nPCB);
}
