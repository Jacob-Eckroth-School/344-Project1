
#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
void listAppend(struct linkedList* list, struct movie* moviePointer) {

	//if the list head exists
	if (list->head) {
		list->tail->next = moviePointer;
		list->tail = moviePointer;
	}
	else {
		list->head = moviePointer;
		list->tail = moviePointer;
	}
	(list->amountOfMovies)++;
}

struct linkedList* initializeList() {
	struct linkedList* list = (struct linkedList*)malloc(sizeof(struct linkedList));
	list->head = NULL;
	list->tail = NULL;
	list->amountOfMovies = 0;
	return list;
}


void printAllMovies(struct linkedList* list) {
	struct movie* traveler = list->head;
	while (traveler) {
		printMovieInfo(traveler);
		traveler = traveler->next;
	}
}

void freeList(struct linkedList* list) {
	struct movie* traveler = list->head;
	struct movie* travelerNext = list->head->next;

	while (traveler) {
		clearMovieMemory(traveler);
		traveler = travelerNext;
		if (traveler) {
			travelerNext = traveler->next;
		}
	}
	free(list);
}




void showListYear(struct linkedList* list) {
	int year = getYearInput();
	bool moviesShown = false;

	struct movie* traveler = list->head;
	while (traveler) {
		if (traveler->year == year) {
			printf("%s\n", traveler->title);
			if (!moviesShown) {
				moviesShown = true;
			}
		}
		traveler = traveler->next;
	}
	if (!moviesShown) {
		printf("No movies exist for the year %d\n", year);
	}
}

void showListRating(struct linkedList* list) {
	int maxYear = 0;
	int minYear = 1000000;
	struct movie* traveler = list->head;
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

	for (int i = 0; i < range; i++) {
		if (bestMovies[i]) {	//not every year will have a movie, so we check
			printf("%d %.1f %s\n", bestMovies[i]->year, bestMovies[i]->rating, bestMovies[i]->title);
		}
	}

	free(bestMovies);


}

void showListLanguage(struct linkedList* list) {
	char language[21];
	printf("Enter the language for which you want to see movies: ");
	scanf("%s", language);
	bool moviesShown = false;

	struct movie* traveler = list->head;
	while (traveler) {
		bool languageFound = false;
		for (int i = 0; i < traveler->amountOfLanguages; i++) {
			if (strcmp(traveler->languages[i], language) == 0) {
				languageFound = true;
			}
		}
		if (languageFound) {
			if (!moviesShown) {
				moviesShown = true;
			}
			printf("%d %s\n", traveler->year, traveler->title);
		}
		
		traveler = traveler->next;
	}
	if (!moviesShown) {
		printf("No movies exist in the language %s\n", language);
	}

}


int getYearInput() {
	printf("Enter the year for which you want to see movies: ");
	int year;
	scanf("%d", &year);
	return year;

}