/*
 * pcb.h
 *
 *  Created on: Feb. 27, 2020
 *      Author: farou
 */

#ifndef PCB_H_
#define PCB_H_

typedef struct PCB{
int PC;
int start;
int end;
int pageTable[10];
int PC_page;
int PC_offset;
int pages_max;
char *fileName;// a changer
}PCB;

struct PCB *makePCB(int start, int end,int pages_max);

void clearFrame(struct PCB *thisPCB,int pageNumber);

void clearPCB( struct PCB *nPCB);
#endif /* PCB_H_ */
