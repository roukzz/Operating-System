#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "kernel.h"

// clear every ram cell To NULL
void initializeRam(char *array[]) {
	for (int i = 0; i < 1000; i++) {
		array[i] = NULL;
	}
}

// find an empty cell in ram
int nextRamCell(char *array[]) {
	int counter = 0;
	while (array[counter] != NULL && counter < 1000) {
		counter++;
	}
	return counter;
}
//set specific ram's cells to NULL
void emptyRam(int start, int end) {
	for (int k = start; k < end; k++) {
		ram[k] = NULL;
	}
}

// add to ram
void addToRAM(FILE *p, int *start, int *end) {
// index of the first empty cell
	*start = nextRamCell(ram);
	// at the begining end point to the same place as start
	*end = *start;

	char buffer[1000];

	// read line one by one till the end of the file
	while (fgets(buffer, sizeof(buffer), p)) {
		// if the file contains more than 1000 lines return error
		if (*end > 999) {
			printf("Load Error: RAM memory is full!");
		}
		// populate ram array
		if (strcmp(buffer, "\n") == 0) {
			fgets(buffer, 999, p);
			continue;
		}
		ram[*end] = strdup(buffer);
		*end = *end + 1;
	}

	*end = *end - 1;

	// close file
	fclose(p);

}

