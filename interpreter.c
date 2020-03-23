/*
 ============================================================================
 Name        : interpreter.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shellmemory.h"
#include "shell.h"
#include "kernel.h"
#include "ram.h"

// quit command
int quit(void) {
	printf("Bye!\n");
	exit(0);
}
// help command
int help(void) {
	printf("quit				Description:Exits\n ");
	printf("help 				Description: Displays all the commands\n");
	printf("set VAR STRING  	Description: assign value to shell memory\n");
	printf("print VAR d			Description: displays the string assigns to VAR\n");
	printf("run SCRIPT.TXT 		Description: Executes the file SCRIPT.TXT\n");
	printf("exec p1 p2 p3 		Description: Executes concurrent programs\n");
	return 0;
}
// set variables to value command
int set(char *words[]) {
	// call add function in shellmemory
	int err = add(words[1], words[2]);
	return err;
}
// print value command
int print(char *words[]) {
	// call printList function in shellmemory
	int err = printList(words[1]);
	return err;
}
// run script command
int run(char *words[]) {
	int err = 0;
	char line[1000];

	FILE *p;

	const char delim[10] = { 10, ' ', 13, 0 };
	char * token;

	// read file.txt
	p = fopen(words[1], "r");
	// if the file doesnt exist
	if (p == NULL) {
		printf("Script not found\n");
		return 0;
	}
	// get the first line
	fgets(line, 999, p);
	// iterate through the lines till the end
	while (!(feof(p))) {
		// quit the script when quit line was seen
		printf("line: %s\n", line);
		token = strtok(line, delim);
		printf("token: %s\n", token);

		// when end of file is not quit
		if (token == NULL) {
			return 0;
		}
		if ((strcmp(token, "quit")) == 0) {
			printf("end of script \n");
			return 0;

		}

		err = parse(line);

		if (err != 0) {
			fclose(p);
			return err;
		}

		fgets(line, 999, p);

	}
	// close the file
	fclose(p);
	return err;

}

int exec(char * words[], int argc) {

	char* loadedFile[3];
	int err = 0;
	int counter = 0;

	for (int i = 1; i < argc; i++) {
		//check if input is valid
		FILE *p = fopen(words[i], "r");
		if (p == NULL) {
			printf("ERROR. %s not found.\n", words[i]);
			clearEverything();
			return err;
		} else
			fclose(p);
	}

	// verify duplicate elements
	for (int i = 1; i < argc; i++) {
		for (int j = 0; j < counter; j++) {
			// duplicate element detected
			if (strcmp(words[i], loadedFile[j]) == 0) {
				//printf("i = %d",i);
				printf("%s already loaded.\n", words[i]);
				clearEverything();
				return err;
			}
		}

		err = myInit(words[i]);
		if (err == 1) {
			clearEverything();
			return 0;
		}
		loadedFile[i - 1] = words[i];
		counter++;
	}
	scheduler();
	initializeRam(ram);
	return err;
}

// interpret the commands
int interpreter(char *words[], int argc) {

	int errCode = 0;

	if ((strcmp(words[0], "quit")) == 0) {
		quit();

	} else if ((strcmp(words[0], "help")) == 0) {
		errCode = help();

	} else if ((strcmp(words[0], "set")) == 0) {

		errCode = set(words);

	} else if ((strcmp(words[0], "print")) == 0) {
		errCode = print(words);

	} else if ((strcmp(words[0], "run")) == 0) {

		errCode = run(words);

	} else if ((strcmp(words[0], "exec")) == 0) {

		if (argc <= 1) { // only exec as argument
			printf("insufficient arguments");
			errCode = 0;

		} else {
			errCode = exec(words, argc);
		}

	}

	else {
		errCode = 2;
	}

	return errCode;
}
