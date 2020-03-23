/*
 * cpu.h
 *
 *  Created on: Feb. 28, 2020
 *      Author: farou
 */

#ifndef CPU_H_
#define CPU_H_

struct thisCPU {
	int IP;
	char IR[1000];
	int quanta;
};

int runQuanta(int quanta);
extern struct thisCPU CPU;
extern int status;

#endif /* CPU_H_ */
