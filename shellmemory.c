
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct MEM{
	char*var;
	char *value;
} arr;

arr arrayMem[100];
int count=0;

int add(char array[] , char value[]){

	// put element when array is empty
	if (arrayMem[0].var == NULL){
		arrayMem[0].var = strdup(array);
		arrayMem[0].value= strdup(value);
		count ++;
	} else {
		//detect duplicate element
		for (int i = 0; i < count;i++){
			if (strcmp(arrayMem[i].var,array) == 0){
				arrayMem[i].value = strdup(value);
				return 0;
			}
		}
		// insert element when not duplicate and when not empty array
		arrayMem[count].var = strdup(array);
		arrayMem[count].value= strdup(value);
		count++;
	}


	return 0;
}

int printList(char var[]){

	// print element that exists in the memory
	for (int i=0; i <count;i++ ){
		if (strcmp(arrayMem[i].var,var) == 0){
			printf(" %s\n",arrayMem[i].value);
		return 0 ;
		}
	}
	// variable doesnt exist in the memory
	printf("Variable does not exist\n");
return 0;
}

