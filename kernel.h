/*
 * kernel.h
 *
 *  Created on: Feb. 24, 2020
 *      Author: farou
 */

#ifndef KERNEL_H_
#define KERNEL_H_

extern char * ram[1000];
extern int pcbCounter;

int myInit(char * fileName );
void scheduler();
void clearEverything();


#endif /* KERNEL_H_ */
