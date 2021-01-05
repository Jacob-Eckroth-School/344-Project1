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
void inputLoop(struct linkedList* list);
void printChoices();

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

	inputLoop(movieList);

	freeList(movieList);
}


void printStartInfo(struct linkedList* list, char* fileName) {
	printf("Processed %s and parsed data for %d movies\n\n", fileName, list->amountOfMovies);
}



//loops until the user decides to exit. 
void inputLoop(struct linkedList* list) {
	bool looping = true;
	while (looping) {
		printChoices();
	}


}


//prints all the choices for the 
void printChoices() {
	printf("\n1. Show movies released in the specified year\n");
	printf("2. Show highest rated movie for each year\n");
	printf("3. Show the title and year of release of all movies in a specific language\n");
	printf("4. Exit from the program\n\n");
	printf("Enter a choice from 1 to 4: ");
}