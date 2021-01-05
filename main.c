/*
Name: Jacob Eckroth
Date: 1/18/2021
Project Name: Assignment 1: Movies
Description:
*/
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "movie.h"
#include "linkedList.h"

bool fileExists(char*);
void runProgram(char*);
void printStartInfo(struct linkedList* list, char*);

int main(int argc, char**argv) {
	if (argc == 2) {
		if (fileExists(argv[1])) {
			runProgram(argv[1]);
		}
		else {
			printf("That file does not exist, please run the program with a file that exists \n");
		}
	}
	else {
		printf("Incorrect amount of arguments suppplied, please try again \n");
		return 0;
	}

	return 0;
}


//returns 1 if file exists, 0 otherwise
bool fileExists(char* fileName) {
		return !(access(fileName, F_OK));
}



void runProgram(char* fileName) {
	FILE* file;
	file = fopen(fileName, "r");
	char line[1000];


	fgets(line, 1000, file);			//gets rid of the annoying top line
	struct linkedList* movieList = initializeList();
	struct movie* moviePointer;
	
	while (fgets(line, 1000, file) != NULL) {		//goes through every line.
		
		moviePointer = allocateMovie(line);
		listAppend(movieList, moviePointer);
	}
	fclose(file);


	printStartInfo(movieList, fileName);






	freeList(movieList);
}


void printStartInfo(struct linkedList* list, char* fileName) {
	printf("Processed %s and parsed data for %d movies\n\n", fileName, list->amountOfMovies);
}