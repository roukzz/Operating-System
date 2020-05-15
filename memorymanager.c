#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kernel.h"
#include <string.h>
#include "pcb.h"
#include "kernel.h"



int pages_max;
int frame;
PCB* pcbArray[10];// array where key correspond to frame and value to a pcb
// count the total pages of a file
int countTotalPages(FILE *f) {
	double lines = 0;
	double pages = 0;
	char c;

	//count lines in text file
	c = fgetc(f);
	while (c != EOF) {
		c = fgetc(f);
		if (c == '\n') {
			lines++; // line counter
		}
	}
	fclose(f);

	// round up
	pages = ceil(lines / 4);

	return (int) pages;
}

int findFrame() { // return a value of a frame in ram when it is empty

	int frame;
	// search for empty frame
	for (int i = 0; i < 40; i = i + 4) {
		if (ram[i] == NULL) {
			frame = i;
			return frame / 4;
		}

	}
	return -1;

}

int findVictim(PCB *p) { // when all frames are occupied we need to select a victim
	int r = rand() % 10;
	int count = 0;

	while (count < 10) {

		if (r == p->pageTable[count]) { // when random number equals to a frame already associated with a page from that pcb
			r = (r + 1) % 10; // increment random number
			count = 0;
		}
		count++;
	}
	// return the victim number
	return r;

}

void updatePageTable(PCB *p, int pageNumber, int frameNumber, int victimFrame) {

	if (frameNumber != -1) { // when there is an empty frame in RAM, just update pcbArray and the page table of the currentPCB
		p->pageTable[pageNumber] = frameNumber; // update page table
		pcbArray[frameNumber] = p; // update pcbArray
	} else { // when ram full and we selected a victim frame
		p->pageTable[pageNumber] = victimFrame; // update page table of the current pcb

		PCB *lastPcb = pcbArray[victimFrame];
		// update the page table of the victim pcb, we want to find the page number associated to the victimframe
		for (int i = 0; i < 10; i++) {

			if (lastPcb->pageTable[i] == victimFrame) {
				lastPcb->pageTable[i] = -2; //no frame associated with that page
			}
		}
		//update the pcbArray
		pcbArray[victimFrame] = p;
	}

}

void loadPage(int pageNumber, FILE *f, int frameNumber) {
// OUBLIE PAS SI FILE NE REUSSIS PAS A OUVRIR

	pageNumber = pageNumber + 1; // i added (+1) only for calculation purpose

	int bool = 0;
	int currentLine = 1; // first line of the file
	int cellToPopulate = frameNumber * 4;
	int maxCell = cellToPopulate + 3;
	int lineNumber = (pageNumber * 4) - 3;
	char line[256];

	while (fgets(line, sizeof line, f) != NULL) {
		if (currentLine == lineNumber) {
			if (cellToPopulate > maxCell) { //when 4 lines of code got in ram
				int bool = 1;
				break;
			} else {

				// populate the right cell
				ram[cellToPopulate] = strdup(line);
				lineNumber++;
				currentLine++;
				cellToPopulate++;
			}

		} else {
			if (bool != 0) {
				break;
			}

			currentLine++;
		}

	}
	fclose(f);
}






int launcher(FILE *p, char* destPath) {

	FILE *target;
	char ch;

	// create the file in backing store
	target = fopen(destPath, "w");

	// copy in the backing store
	while ((ch = fgetc(p)) != EOF)
		fputc(ch, target);
	//printf("File copied successfully.\n");
	// close the original file
	fclose(p);
	fclose(target);	   // close the copied file

	// target which is the file in the backing store opened to count total pages
	target = fopen(destPath, "r");

	if (target == NULL) {
		printf("Could not open file\n");
		return 0;
	} else {
		// total pages for a propram
		pages_max = countTotalPages(target);
	}

	//create pcb for that process
	PCB *pp = makePCB(0, 0, pages_max);
	pp->fileName = strdup(destPath); // pcb has a file name associated with
	// pc points to the first line of the specific program
	pp->PC = findFrame() * 4;
	// load at the most 2 pages at launch time
	for (int i = 0; i < 2; i++) {

		frame = findFrame();
		// case where at launch time all ram is full so we exceed the number allowed of program which is 3
		if (frame == -1) {
			printf("error: load first page of the program was not possible!!");
			return -1;
		} else if (i < pages_max) {
			// we load page the first page into the ram, so for each program we gonna load only one page at launch time
			loadPage(i, fopen(destPath, "r"), frame);
			updatePageTable(pp, i, frame, -10);

		}

	}


	addToReady(pp);

	return 0;

}
