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
#include "colors.h"

bool fileExists(char*);
void runProgram(char*);
void printStartInfo(struct linkedList* list, char*);
void inputLoop(struct linkedList* list);
void printChoices();
int getChoiceInput();

int main(int argc, char**argv) {
	if (argc == 2) {
		if (fileExists(argv[1])) {
			runProgram(argv[1]);
		}
		else {
			printError("That file does not exist, please run the program with a file that exists \n");
		}
	}
	else {
		printError("Incorrect amount of arguments suppplied, please try again \n");
		return 0;
	}

	return 0;
}



/*
** Description: Returns true if file exists, 0 otherwise
** Prerequisites: fileName is defined
** Updated/Returned: returns true if the file exists, 0 otherwise.
*/
bool fileExists(char* fileName) {
		return !(access(fileName, F_OK));
}


/*
** Description: Runs the main program, with the filename as the input
** Prerequisites: fileName is a valid file that exists
** Updated/Returned: changes nothing, no returns
*/
void runProgram(char* fileName) {
	FILE* file = fopen(fileName, "r");
	char* line = NULL;
	size_t len = 0;
	ssize_t nread;

	//gets rid of the first line which is pointless.
	getline(&line, &len, file);
	struct linkedList* movieList = initializeList();
	struct movie* moviePointer;
	
	while ((nread = getline(&line,&len,file)) != -1) {		//goes through every line other than the first one
		moviePointer = allocateMovie(line);	//parses the line into the movie struct
		listAppend(movieList, moviePointer); //adds the movie struct to the linked list

	}
	free(line);
	fclose(file);


	printStartInfo(movieList, fileName);

	//main input loop
	inputLoop(movieList);

	
	freeList(movieList);
}



/*
** Description: Prints how many movies were processed from the filename
** Prerequisites: fileName is defined, list is allocated.
** Updated/Returned: Nothing is changed, no returns
*/
void printStartInfo(struct linkedList* list, char* fileName) {
	printf("Processed %s and parsed data for %d movies\n\n", fileName, list->amountOfMovies);
}



/*
** Description: Loops the input choices until the user decides to exit
** Prerequisites: list is allocated
** Updated/Returned: No updates
*/
void inputLoop(struct linkedList* list) {
	bool looping = true;
	while (looping) {
		
		int choice = getChoiceInput();
		
		switch (choice) {
		case 1:
			showListYear(list);
			break;
		case 2:
			showListRating(list);
			break;
		case 3:
			showListLanguage(list);
			break;
		case 4:
			looping = false;
			break;
		default:

			break;
		}
	}


}

/*
** Description: Gets input between 1-4 from the user
** Prerequisites: None
** Updated/Returned: returns an int 1-4
*/
int getChoiceInput() {
	bool valid = false;
	int choice = 0;
	char userInput[20];
	while (!valid) {
		printChoices();
		setCyan();
		scanf("%s", userInput);
		resetColor();
		if (strlen(userInput) != 1) {
			valid = false;
		}
		else {
			//bounds checking
			if (userInput[0] - '0' >= 1 && userInput[0] - '0' <= 4) {
				choice = userInput[0] - '0';
				valid = true;
			}
			else {
				valid = false;
			}
		}
		
		if (!valid) {
			setRed();
			printError("You entered an incorrect choice. Try again.\n");
			resetColor();
		}
	}
	return choice;

}

/*
** Description: Prints all the choices for the user to pick from
** Prerequisites: None
** Updated/Returned: None
*/
void printChoices() {
	printf("\n1. Show movies released in the specified year\n");
	printf("2. Show highest rated movie for each year\n");
	printf("3. Show the title and year of release of all movies in a specific language\n");
	printf("4. Exit from the program\n\n");
	printf("Enter a choice from 1 to 4: ");
}