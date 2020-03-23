/*
 * pcb.h
 *
 *  Created on: Feb. 27, 2020
 *      Author: farou
 */

#ifndef PCB_H_
#define PCB_H_

struct PCB{
int PC;
int start;
int end;
};

struct PCB *makePCB(int start, int end);

void clearPCB( struct PCB *nPCB);
#endif /* PCB_H_ */
