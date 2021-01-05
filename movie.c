#include "movie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMovieTitle(struct movie* moviePointer) {
	printf("%s", moviePointer->title);


}

void printMovieInfo(struct movie* moviePointer) {
	printf("Title: %s\n", moviePointer->title);
	printf("Year: %d\n", moviePointer->year);
	printf("Languages:");
	for (int i = 0; i < moviePointer->amountOfLanguages; ++i) {
		printf("%s,", moviePointer->languages[i]);
	}
	printf("\n");
	printf("Rating: %.1f\n", moviePointer->rating);
}

void printMovieLanguages(struct movie* moviePointer) {

	for (int i = 0; i < moviePointer->amountOfLanguages; ++i) {
		
		printf("%s, ", moviePointer->languages[i]);
		
	}
}


void clearMovieMemory(struct movie* moviePointer) {
	free(moviePointer->title);
	for (int i = 0; i < moviePointer->amountOfLanguages; ++i) {
		free(moviePointer->languages[i]);

	}
	free(moviePointer->languages);

	free(moviePointer);
}


struct movie* allocateMovie(char* fullLine) {
	struct movie* moviePointer = (struct movie*)malloc(sizeof(struct movie));

	char* savePointer;
	char* token = strtok_r(fullLine, ",", &savePointer);

	moviePointer->title = (char*)malloc((strlen(token) + 1) * sizeof(char));	//+1 because strlen doesn't include null
	strcpy(moviePointer->title, token);


	//year
	token = strtok_r(NULL, ",", &savePointer);
	moviePointer->year = atoi(token);

	token = strtok_r(NULL, ",", &savePointer);
	assignMovieLanguages(token, moviePointer);


	//rating
	token = strtok_r(NULL, "\n", &savePointer);
	moviePointer->rating = strtod(token, 0);

	return moviePointer;
}

void assignMovieLanguages(char* languages, struct movie* moviePointer) {
	char* savePointer;

	char* removeFirstBracket;
	removeFirstBracket = strtok_r(languages, "[", &savePointer);
	char* token = strtok_r(removeFirstBracket, "]", &savePointer);
	token = strtok_r(removeFirstBracket, ";", &savePointer);
	int amountOfLanguages = 0;
	moviePointer->languages = (char**)malloc(sizeof(char*));
	while (token) {
		++amountOfLanguages;
		moviePointer->languages = (char**)realloc(moviePointer->languages, (sizeof(char*) * amountOfLanguages));

		moviePointer->languages[amountOfLanguages - 1] = malloc((strlen(token) + 1) * sizeof(char));
		strcpy(moviePointer->languages[amountOfLanguages - 1], token);

		token = strtok_r(NULL, ";", &savePointer);
	}
	moviePointer->amountOfLanguages = amountOfLanguages;
}





