//Michael McAdaragh 5/23/2026
//Conway's Game of Life.cpp

//#include <iostream>
#include "raylib.h"
#include "GameOfLife.h"

using namespace std;

int main()
{	
	SetConfigFlags(FLAG_WINDOW_UNDECORATED);
	InitWindow(0, 0, "Game Of Life");	// Initializes a window the size of the screen	via raylib
	
	int width = GetScreenWidth();		// Get Width and Height Dynamically via raylib
	int height = GetScreenHeight();
	
	SetTargetFPS(60);							// Limit framerate to 60fps
	width /= CELLSIZE;							// Adjust width and height to refer to number of cells instead of number of pixels
	height /= CELLSIZE;

	//2D arrays on heap. Roles switch each iteration like flipping an hourglass.

	int* grid_ptr = new int[height*width];				//store intial cell states
	int* helper_grid_ptr = new int[height * width];		//record judgements

	empty_grid(width, height, grid_ptr);				//initialize all cells as "dead" i.e. "0"
	empty_grid(width, height, helper_grid_ptr);			//empty_grid(helper_grid_ptr); is technically redundant. see array_alternator function.
	
	seed_life(width, height, grid_ptr);
	int generation = 0;
	display(width, height, grid_ptr, generation);		//display initial "field of life".
	double lastUpdateTime = GetTime();					// Using "GetTime() raylib function to Control speed of iterations."
	do
	{
		if (GetTime() - lastUpdateTime >= 0.5)
		{
			if (generation % 2 == 0)	//iteration even
				matrix_alternator(width, height, grid_ptr, helper_grid_ptr, generation);

			if (generation % 2 == 1)	//iteration odd
				matrix_alternator(width, height, helper_grid_ptr, grid_ptr, generation);
		
			generation++;
			lastUpdateTime = GetTime();
		}
	} while (WindowShouldClose() == false);

	return 0;
}