#ifndef LINKEDLIST
#define LINKEDLIST
#include "movie.h"
struct linkedList {
	struct movie* head;
	int amountOfMovies;
	struct movie* tail;
};

void listAppend(struct linkedList* list, struct movie*);
struct linkedList* initializeList();

void printAllMovies(struct linkedList* list);

void freeList(struct linkedList* list);
#endif