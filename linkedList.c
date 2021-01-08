
#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "colors.h"

/*
** Description: Appends a movie pointer to a linked list
** Prerequisites: list and moviePointer are allocated
** Updated/Returned: linked list is updated to have the movie pointer at the end
*/
void listAppend(struct linkedList* list, struct movie* moviePointer) {
	assert(list);
	//if the list head exists
	if (list->head) {
		list->tail->next = moviePointer;
		list->tail = moviePointer;
	}
	//else if the list has no items in it.
	else {
		list->head = moviePointer;
		list->tail = moviePointer;
	}
	(list->amountOfMovies)++;
}


/*
** Description: Initializes and returns a pointer to a linked list
** Prerequisites: none
** Updated/Returned: Returns an empty linked list.
*/
struct linkedList* initializeList() {
	struct linkedList* list = (struct linkedList*)malloc(sizeof(struct linkedList));
	list->head = NULL;
	list->tail = NULL;
	list->amountOfMovies = 0;
	return list;
}



/*
** Description: Frees all memory associated with a linked list
** Prerequisites: linked list is allocated
** Updated/Returned: memory of linked list is freed
*/
void freeList(struct linkedList* list) {
	assert(list);
	struct movie* traveler = list->head;
	struct movie* travelerNext = list->head->next;


	//frees every movie in the linked list
	while (traveler) {
		assert(traveler);
		clearMovieMemory(traveler);
		traveler = travelerNext;
		if (traveler) {
			travelerNext = traveler->next;
		}
	}
	free(list);
}



/*
** Description: Prints all movies of a certain year chosen by the user
** Prerequisites: linked list is allocated
** Updated/Returned: None updated, prints to screen.
*/
void showListYear(struct linkedList* list) {
	assert(list);
	int year = getYearInput();
	bool moviesShown = false;
	

	//iterates through a list and prints a movie made in a certain year
	struct movie* traveler = list->head;
	setGreen();
	while (traveler) {
		if (traveler->year == year) {
			printf("%s\n", traveler->title);
			if (!moviesShown) {
				moviesShown = true;
			}
		}
		traveler = traveler->next;
	}
	resetColor();
	if (!moviesShown) {
		setRed();
		printf("No data available for movies released in the year %d.\n", year);
		resetColor();
	}
}


/*
** Description: prints the movie with the best rating from every year
** Prerequisites: linked list is allocated
** Updated/Returned: None updated, prints to screen.
*/
void showListRating(struct linkedList* list) {
	assert(list);
	int maxYear = 0;
	int minYear = 1000000;
	struct movie* traveler = list->head;

	//calculates the minimum and maximum year
	while (traveler) {
		if (traveler->year > maxYear) {
			maxYear = traveler->year;
		}
		if (traveler->year < minYear) {
			minYear = traveler->year;
		}
		traveler = traveler->next;
	}

	int range = maxYear - minYear + 1;	//the range of the years that we'll look at. 
	//+ 1 because If max year and min year are the same then we'll want to store 1different movies at least.
	
	//creates an array of movie pointers with everythign initialized to null.
	//this will be our hash table.
	struct movie** bestMovies = (struct movie**)calloc(range, sizeof(struct movie*));
	traveler = list->head;
	while (traveler) {

		//if the hash table already has something in it, otherwise we just put the movie we're looking at right now into that spot
		if (bestMovies[traveler->year - minYear]) {
			//if the new rating is higher
			if (traveler->rating > bestMovies[traveler->year - minYear]->rating) {
				bestMovies[traveler->year - minYear] = traveler;
			}
		}
		else {
			bestMovies[traveler->year - minYear] = traveler;
		}
		traveler = traveler->next;
	}
	setGreen();
	for (int i = 0; i < range; i++) {
		if (bestMovies[i]) {	//not every year will specifically have a movie, so we check if there's a value
			
			printf("%d %.1f %s\n", bestMovies[i]->year, bestMovies[i]->rating, bestMovies[i]->title);
		}
	}
	resetColor();
	free(bestMovies);


}


/*
** Description: Prints all the movies with a certain language. Case sensitive
** Prerequisites: linked list is allocated
** Updated/Returned: None updated, prints to screen.
*/
void showListLanguage(struct linkedList* list) {
	assert(list);
	size_t bufsize = 21;
	char* language = (char*)malloc(bufsize * (sizeof(char)));
	printf("Enter the language for which you want to see movies: ");
	setCyan();
	getline(&language, &bufsize, stdin);
	language[strlen(language) - 1] = 0; //getting rid of newline character left over from getline
	resetColor();
	bool moviesShown = false;

	struct movie* traveler = list->head;
	while (traveler) {
		bool languageFound = false;

		//iterates through all the possible languages for a movie
		for (int i = 0; i < traveler->amountOfLanguages; i++) {
			if (strcmp(traveler->languages[i], language) == 0) {
				languageFound = true;
			}
		}
		if (languageFound) {
			if (!moviesShown) {
				moviesShown = true;
			}
			setGreen();
			printf("%d %s\n", traveler->year, traveler->title);
			resetColor();
		}
		
		traveler = traveler->next;
	}
	setRed();
	if (!moviesShown) {
		
		printf("No data available on movies in the language %s.\n", language);
		
	}
	resetColor();
	free(language);

}
/*
** Description: Returns an int based on user input for the year. No bounds checking
** Prerequisites: None
** Updated/Returned: Returns an int entered by user. As stated by assignment, we assume that the user enters a correct number. It works fine if they don't though.
*/
int getYearInput() {
	printf("Enter the year for which you want to see movies: ");
	size_t bufsize = 10;
	char* userInput = (char*)malloc(bufsize * (sizeof(char)));

	setCyan();
	getline(&userInput, &bufsize, stdin);
	resetColor();
	userInput[strlen(userInput) - 1] = 0;			//getting rid of newline character left over from getline
	int year = atoi(userInput);
	

	free(userInput);
	return year;

}


