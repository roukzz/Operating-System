/*
 * launcher.h
 *
 *  Created on: Mar. 25, 2020
 *      Author: farou
 */

#ifndef MEMORYMANAGER_H_
#define MEMORYMANAGER_H_

//extern char *ramTest[40];
int launcher(FILE *p, char* destPath);
void loadPage(int pageNumber, FILE *f, int frameNumber);
void updatePageTable(PCB *p, int pageNumber,int frameNumber, int victimFrame);
int findVictim(PCB *p);
int findFrame();
void ini();


#endif /* MEMORYMANAGER_H_ */
