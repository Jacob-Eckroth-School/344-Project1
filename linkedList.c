
#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>

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