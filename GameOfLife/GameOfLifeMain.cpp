//Michael McAdaragh 5/23/2026
//Conway's Game of Life.cpp

#include <iostream>

#include "GameOfLife.h"

using namespace std;

int main()
{	
	//2D arrays on heap. Roles switch each iteration like an oscillating slinky.

	int* grid_ptr = new int[HEIGHT*WIDTH];		//store intial cell states
	int* helper_grid_ptr = new int[HEIGHT * WIDTH];		//record judgements

	empty_grid(grid_ptr);						//initialize all cells as "dead" i.e. "0"
	empty_grid(helper_grid_ptr);				//empty_grid(helper_grid_ptr); is technically redundant. see array_alternator function.
	
	seed_life(grid_ptr);				//needs to be passed engine for random numbers.
	display(grid_ptr);							//display initial "field of life".

	int generation = 0;
	do
	{
		if(generation % 2 == 0) //iteration even
		{
			array_alternator(grid_ptr, helper_grid_ptr);
		}

		if(generation % 2 == 1)	//iteration odd
		{
			array_alternator(helper_grid_ptr, grid_ptr);
		}
		generation++;
		cout << "Generation: " << generation << endl;
		this_thread::sleep_for(chrono::milliseconds(4000));	//slows program execution
	} while (1);

	return 0;
}

/* SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	start_SDL3(window, renderer);

	//1.) Clears the screen to a black background first.
	SDL_RenderClear(renderer);

	//2.) This sets the paintbrush color to bright Red(255 Red, 0 Green, 0 Blue, 255 Alpha).
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	//3.)
	SDL_FRect thiccPixel;
	thiccPixel.x = 320.0f;		//screen x position.
	thiccPixel.y = 240.0f;		//screen y position.
	thiccPixel.w = 10.0f;		//width of the block.
	thiccPixel.h = 10.0f;		//height of the block.

	//4.)This flashes your drawings onto the moniter instantly.
	SDL_RenderPresent(renderer);
	this_thread::sleep_for(chrono::milliseconds(4000)); */	//slows program execution