#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "ram.h"
#include "pcb.h"
#include "cpu.h"
#include "kernel.h"
#include <io.h>
#include "memorymanager.h"





char *ram[40];
PCB* pcbArray[10];
int pcbCounter = 0;

typedef struct Node {
	struct PCB* nPCB;
	struct Node* next;
} Node;

Node *head = NULL;
Node *tail = NULL;

// initialise ram to NULL
void ini(){

	for (int i = 0; i < 40; i++) {
			ram[i] = NULL;
			}
}
// initialize pcb array to NULL
void iniPcbArray(){
	for (int i=0;i<10;i++){
		pcbArray[i]=NULL;
	}
}


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




void scheduler(){
	int isEnque=0;

	while (head != NULL && tail !=NULL){// while le ready queue is not empty

		Node*current_process = removeHead(); // pop the head pcb

		struct PCB*currentPCB = current_process->nPCB;

		CPU.offset=currentPCB->PC_offset;

		CPU.IP = currentPCB->PC;

		isEnque=runQuanta(2);// run process for 2 quanta

		if (isEnque == -2){ // when page fault occurs
			clearFrame(currentPCB,currentPCB->PC_page);
			currentPCB->PC_page++;

			if (currentPCB->PC_page == currentPCB->pages_max){
						//clear ram et remove this pcb from queue
				clearPCB(currentPCB);
					}else {
						if (currentPCB->pageTable[currentPCB->PC_page]!=-2){ // page is in ram pc points to a new frame
							currentPCB->PC= currentPCB->pageTable[currentPCB->PC_page]*4;
							currentPCB->PC_offset=0;

						} else {
							// find victim
							int frame= findFrame();
							if (findFrame()!=-1){// when there is empty frame in ram
								loadPage(currentPCB->PC_page,(fopen(currentPCB->fileName,"r")),frame);
								updatePageTable(currentPCB,currentPCB->PC_page,frame,-10);


							} else{ // when all frame occupied--> find victim
								int victim = findVictim(currentPCB);
								loadPage(currentPCB->PC_page,(fopen(currentPCB->fileName,"r")),victim);
								updatePageTable(currentPCB,currentPCB->PC_page,-1,victim);
							}
							currentPCB->PC = currentPCB->pageTable[currentPCB->PC_page]*4;
							currentPCB->PC_offset=0;
						}
						addToReady(currentPCB);
					}
		}
		 else if(isEnque == -1){
			// clear the pcb clear the ram update pcbArray
			 clearPCB(currentPCB);

		} else {
			currentPCB->PC_offset=CPU.offset;
			currentPCB->PC=currentPCB->pageTable[currentPCB->PC_page]*4+currentPCB->PC_offset;
			addToReady(currentPCB);

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



void boot(){
	// set every cell to NULL
	ini();
	// deletes former directory
	char deleteCmd[30]= "rmdir /q /s BackingStore";
	system (deleteCmd);


	// creating backingStore directory
	char *BackingStore = "./BackingStore";
	int dir = mkdir(BackingStore);


}

int kernel(){


	char prompt[100] = { '$', '\0' };
	char userInput[1000];
	int errorCode = 0;

	printf("Kernel 1.0 loaded!\n");
	printf("Welcome to the Farouk Arab Shell! \n");
	printf("Version 3.0 Updated April 2020 \n");

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
					printf("Unknown command\n");
				} else if (errorCode ==-1){

					printf("there is more than 10 programs to execute!!");

				}

			}

	return errorCode;
}

int main(void) {
	int err = 0;

	boot();


	err = kernel();




}
