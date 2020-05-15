#include <stdio.h>
#include "kernel.h"
#include "interpreter.h"
#include <string.h>
#include "cpu.h"
#include "shell.h"

struct thisCPU CPU = { .quanta = 2 };


//execute processes
int runQuanta(int quanta) {

	for (int i = 0; i < quanta; i++) {

		if (ram[CPU.IP+i] == NULL){
			return -1; // this instruction is NULL, which mean we dont want to enque anymore this pcb
		}

		strcpy(CPU.IR, ram[CPU.IP + i]);

		if (pcbCounter != 0 && strstr(CPU.IR, "quit") != 0) { //exit only one script and continue the others

			return -1;
		}
		parse(CPU.IR);

		CPU.offset++;

		if (CPU.offset==4){
			return -2;

		}

	}
	return 1;
}


