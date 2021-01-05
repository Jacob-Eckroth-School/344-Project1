/*
Name: Jacob Eckroth
Date: 1/18/2021
Project Name: Assignment 1: Movies
Description:
*/
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

bool fileExists(char*);
void runProgram(char*);



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


}





