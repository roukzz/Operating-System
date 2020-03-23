/*
 ============================================================================
 Name        : shell.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"




int parse ( char array[]){


	char temp[200];
	char *words[100];

	int a,b;
	int w =0;
	const char delim[10] = { 10 };
			char * token;
			token = strtok(array, delim);



	// eliminate white spaces at the beggining
	for (a=0; array[a]==' ' && a < 1000; a++);

	while (array[a] != '\0' && a <1000){

		for (b=0; array[a] != '\0' && array[a] != ' ' && a<1000  ; a++,b++){
			temp[b] = array[a];
		}
		temp[b]= '\0';

		const char delim[10] = { 10 };
		char * token;
		token = strtok(temp, delim);
		words[w]= strdup(token);

		a++;
		w++;
	}

	words[w]=NULL;


	if (words[0]==NULL){
		printf("empty user input\n");
		return 0;
	}

	return interpreter(words,w);
}

