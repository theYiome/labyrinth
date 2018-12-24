#pragma once
#include <vector>

/*
genrates random maze with diesired width and height
to work properly it needs odd input
*/

typedef struct
{
	int x, y; //Node position - little waste of memory, but it allows faster generation
	void *parent; //Pointer to parent node
	char c; //Character to be displayed
	char dirs; //Directions that still haven't been explored
} Node;

Node* generateLabyrinth(int, int);