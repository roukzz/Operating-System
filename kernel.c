#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "ram.h"
#include "pcb.h"
#include "cpu.h"
#include "kernel.h"

char * ram[1000];
int pcbCounter = 0;

typedef struct Node {
	struct PCB* nPCB;
	struct Node* next;
} Node;

Node *head = NULL;
Node *tail = NULL;

// add element to the queue
void addToReady(struct PCB* pcb) {
	// when there no element in the queue

	if (head == NULL) {
		Node *firstPCB = malloc(sizeof(struct Node));
		firstPCB->nPCB = pcb;
		firstPCB->next = NULL;
		head = firstPCB;
		tail = firstPCB;

	} else {
		Node*lastPCB = malloc(sizeof(struct Node));
		lastPCB->next = tail;
		lastPCB->nPCB = pcb;
		tail = lastPCB;
	}
	pcbCounter++;
}

// remove head element from the queue
struct Node *removeHead() {

	pcbCounter--;

	Node*temp;
	//when only one node
	if (head == tail) {
		temp = head;
		head = NULL;
		tail = NULL;
		return temp;
	} else {
		temp = tail;
		while (temp->next != head) {
			temp = temp->next;
		}

		Node* tmpHead = head;
		temp->next = NULL;
		head = temp;
		return tmpHead;
	}
}

int myInit(char * fileName) {

	FILE *p = fopen(fileName, "r");
	// file could not open
	if (p == NULL) {
		printf("could not open the file  :%s ", fileName);
		clearEverything();
		return 1;
	}
	int start;
	int end;
	// add each command to the ram
	addToRAM(p, &start, &end);
	struct PCB *nPCB = makePCB(start, end);
	// add PCB to the ready queue
	addToReady(nPCB);
	return 0;
}

void scheduler() {
	int isEnQ = 0;

	while (tail != NULL) {

		if (status == 1) {

			status = 0;
			Node*current_process = removeHead();

			struct PCB*thisPCB = current_process->nPCB;
			CPU.IP = thisPCB->PC;

			if (thisPCB->end == thisPCB->start) {
				isEnQ = 0; //case of an empty script
			}

			else if (CPU.IP + CPU.quanta > thisPCB->end + 1) {
				isEnQ = runQuanta(1);

			} else {
				isEnQ = runQuanta(CPU.quanta);

				thisPCB->PC = CPU.IP + CPU.quanta;
				status = 1;
			}
			if (thisPCB->PC > thisPCB->end) {
				isEnQ = 0;
			}
			if (isEnQ == 1) {
				addToReady(thisPCB);
			}

			else {

				clearPCB(thisPCB);
			}

		}
	}
}

// clear the queue and the ram
void clearEverything() {
	while (tail != NULL) {
		Node*current_process = removeHead();
		struct PCB *thisPCB = current_process->nPCB;
		clearPCB(thisPCB);

	}
}

int main(void) {
	char prompt[100] = { '$', '\0' };
	char userInput[1000];
	int errorCode = 0;
	initializeRam(ram);

	printf("Kernel 1.0 loaded!\n");
	printf("Welcome to the Farouk Arab Shell! \n");
	printf("Version 2.0 Updated February 2020 \n");

	while (1) {

		printf("%s", prompt);
		fgets(userInput, 999, stdin);

		errorCode = parse(userInput);
		// reset the user input
		memset(userInput, '\0', sizeof(char) * 1000);

		if (errorCode == 1) {
			exit(0);
		}
		if (errorCode == 2) {
			printf("Unknown CCommand\n");
		}

	}
}
