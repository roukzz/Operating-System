/*
 * kernel.h
 *
 *  Created on: Feb. 24, 2020
 *      Author: farou
 */

#ifndef KERNEL_H_
#define KERNEL_H_
#include "pcb.h"

extern char * ram[40];

extern PCB* pcbArray[10];
extern int pcbCounter;

int myInit(char * fileName );
void scheduler();
void clearEverything();
void ini();
void iniPcbArray();
void addToReady(struct PCB* pcb);


#endif /* KERNEL_H_ */
