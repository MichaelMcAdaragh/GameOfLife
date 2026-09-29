#include "raylib.h"
#include "GameOfLife.h"

//Empty grid
void empty_grid(int width, int height, int* cell_state)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			cell_state[y * width + x] = 0;
		}
	}
}

//get random number
int randomNumber(int low, int high)
{                                                           //"static" keyword used to make sure initialization only occurs once.
	static random_device rd;                                //1.)obtain a random seed from the hardware.
	static mt19937 gen(rd());                               //2.)initialize the standard mersenne_twister_engine with the seed. 
	uniform_int_distribution<> distr(low, high);            //3.)define the range [low / high].
	int randomNum = distr(gen);                             //4.)generate random number.
	return randomNum;
}

void seed_life(int width, int height, int* cell_state)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int live_or_dead = randomNumber(0, 1);			//assigns random number to live_or_dead.
			cell_state[y * width + x] = live_or_dead;
		}
	}
}
// Display grid.
void display(int width, int height, int* cell_state, int generation)
{
	BeginDrawing();											// Starts The Drawing Process, Storing the following intructions to be executed at once later.
	ClearBackground(BLACK);

	for (int y = 0; y < height; y++)						// Go top to bottom thru Game of Life matrix cells.
	{
		for (int x = 0; x < width; x++)
		{
			if (cell_state[y * width + x] == 1)
			{
				DrawRectangle(x * CELLSIZE, y * CELLSIZE, CELLSIZE, CELLSIZE, RAYWHITE);
			}
		}
	}
	char genText[32];
	DrawText(TextFormat("Generation: %d", generation), 20, 20, 30, GREEN);
	EndDrawing();											// Ends the Drawing Process, Executing the stored drawing instructions all at once.
}

//Scan for life.
int scanning_for_life(int width, int height, int* cell_state, int y, int x)
{
	int live_neighbors = 0;
	//outer if() checks grid bounds, inner if() checks for live neighbors.
	if (y + 1 < height && x - 1 > 0)													//top row left to right.
	{
		if (cell_state[(y + 1) * width + (x - 1)] == 1)
		{
			live_neighbors++;
		}
	}
	if (y + 1 < height)
	{
		if (cell_state[(y + 1) * width + (x + 0)] == 1)
		{
			live_neighbors++;
		}
	}
	if (y + 1 < height && x + 1 < width)
	{
		if (cell_state[(y + 1) * width + (x + 1)] == 1)
		{
			live_neighbors++;
		}
	}
	if (x - 1 > 0)																	//middle row left to right.
	{
		if (cell_state[(y + 0) * width + (x - 1)] == 1)
		{
			live_neighbors++;
		}
	}
	if (x + 1 < width)
	{
		if (cell_state[(y + 0) * width + (x + 1)] == 1)
		{
			live_neighbors++;
		}
	}
	if (y - 1 > 0 && x - 1 > 0)														//bottom row left to right.
	{
		if (cell_state[(y - 1) * width + (x - 1)] == 1)
		{
			live_neighbors++;
		}
	}
	if (y - 1 > 0 && x + 1 < width)
	{
		if (cell_state[(y - 1) * width + (x + 1)] == 1)
		{
			live_neighbors++;
		}
	}
	if (y - 1 > 0)
	{
		if (cell_state[(y - 1) * width + (x + 0)] == 1)
		{
			live_neighbors++;
		}
	}
	return live_neighbors;
}

//Cast final judgement on the cells.
void cell_inspector(int width, int* cell_state, int* helper_cell_state, int y, int x, int live_neighbors)
{

	if (cell_state[y * width + x] == 1)						//Rules for living cells:
	{
		if (live_neighbors < 2)								//Underpopulation	
		{													//-- any live cell with < 2 live neighbors dies.
			helper_cell_state[y * width + x] = 0;
			//cout << "cell " << cell_number << " dies from 'underpopulation.'\n";
		}
		if (live_neighbors >= 2 && live_neighbors <= 3)		//Survival			
		{													//-- any live cell with 2 - 3 live neighbors survives to the next generation.
			helper_cell_state[y * width + x] = 1;
			//cout << "cell " << cell_number << " 'survives.'\n";
		}
		if (live_neighbors > 3)								//Overpopulation	
		{													//-- any live cell with > 3 live neighbors dies.
			helper_cell_state[y * width + x] = 0;
			//cout << "cell " << cell_number << " dies from 'overpopulation.'\n";
		}
	}
	if (cell_state[y * width + x] == 0)						//Rules for dead cells:
	{
		if (live_neighbors == 3)							//Reproduction	
		{													//-- any dead cell with exactly 3 neighbors becomes a live cell.
			helper_cell_state[y * width + x] = 1;
			//cout << "cell " << cell_number << " is 'born'.\n";
		}
	}
}

void matrix_alternator(int width, int height, int *cell_state, int* helper_cell_state, int generation)
{
	empty_grid(width, height, helper_cell_state);
	for (int y = 0; y < height; y++)			//top to bottom
	{
		for (int x = 0; x < width; x++)			//left to right
		{
			int live_neighbors = scanning_for_life(width, height, cell_state, y, x);//"scanning for signs of life"
			cell_inspector(width, cell_state, helper_cell_state, y, x, live_neighbors);//"casting final judgement of cell's Life or Death"
		}
	}
	display(width, height, helper_cell_state, generation);
}