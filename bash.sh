#!/bin/bash
gcc -c shell.c interpreter.c shellmemory.c kernel.c ram.c pcb.c cpu.c
gcc -o mykernel shell.o interpreter.o shellmemory.o kernel.o ram.o pcb.o cpu.o 