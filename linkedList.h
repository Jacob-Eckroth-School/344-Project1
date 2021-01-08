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



void freeList(struct linkedList* list);

void showListYear(struct linkedList* list);
void showListRating(struct linkedList* list);
void showListLanguage(struct linkedList* list);
int getYearInput();


#endif