#include <stdio.h>
#include "kernel.h"
#include "interpreter.h"
#include <string.h>
#include "cpu.h"
#include "shell.h"

struct thisCPU CPU = { .quanta = 2 };
int status = 1;

//execute processes
int runQuanta(int quanta) {

	for (int i = 0; i < quanta; i++) {

		strcpy(CPU.IR, ram[CPU.IP + i]);
		if (pcbCounter != 0 && strstr(CPU.IR, "quit") != 0) { //exit only one script and continue the others
			status = 1;
			return 0;
		}
		parse(CPU.IR);
	}
	return 1;
}
