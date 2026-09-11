#include "GameOfLife.h"

//Empty grid
void empty_grid(int* cell_state)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			cell_state[y * WIDTH + x] = 0;
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

void seed_life(int* cell_state)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			int live_or_dead = randomNumber(0, 1);		//assigns random number to live_or_dead.
			cell_state[y * WIDTH + x] = live_or_dead;
		}
	}
}

//Display grid.
void display(int* cell_state)
{

	string frame_buffer;
	frame_buffer.reserve(HEIGHT + 2 * (WIDTH * 2 + 2));

	for (int i = 0; i < WIDTH; i++)	//Print ceiling of grid.
	{
		frame_buffer += "--";
	}
	frame_buffer += "--\n";
	for (int y = 0; y < HEIGHT; y++) //Print tetris grid cells.
	{
		frame_buffer += "|"; //Print left grid wall.
		for (int x = 0; x < WIDTH; x++)
		{
			switch (cell_state[y * WIDTH + x])
			{
			case 0:
				frame_buffer += "  ";
				break;
			case 1:
				frame_buffer += "[]";
				break;
			default:
				return;
			}
		}
		frame_buffer += "|\n"; //Right grid wall.
	}
	//Floor of grid
	for (int i = 0; i < WIDTH; i++)
	{
		frame_buffer += "--";
	}
	frame_buffer += "--\n";
	cout << frame_buffer << flush;
}

//Scan for life.
int scanning_for_life(int* cell_state, int y, int x)
{
	int live_neighbors = 0;
	//outer if() checks grid bounds, inner if() checks for live neighbors.
	if (y + 1 < HEIGHT && x - 1 > 0)													//top row left to right.
	{
		if (cell_state[(y + 1) * WIDTH + (x - 1)] == 1)
		{
			live_neighbors++;
		}
	}
	if (y + 1 < HEIGHT)
	{
		if (cell_state[(y + 1) * WIDTH + (x + 0)] == 1)
		{
			live_neighbors++;
		}
	}
	if (y + 1 < HEIGHT && x + 1 < WIDTH)
	{
		if (cell_state[(y + 1) * WIDTH + (x + 1)] == 1)
		{
			live_neighbors++;
		}
	}
	if (x - 1 > 0)																	//middle row left to right.
	{
		if (cell_state[(y + 0) * WIDTH + (x - 1)] == 1)
		{
			live_neighbors++;
		}
	}
	if (x + 1 < WIDTH)
	{
		if (cell_state[(y + 0) * WIDTH + (x + 1)] == 1)
		{
			live_neighbors++;
		}
	}
	if (y - 1 > 0 && x - 1 > 0)														//bottom row left to right.
	{
		if (cell_state[(y - 1) * WIDTH + (x - 1)] == 1)
		{
			live_neighbors++;
		}
	}
	if (y - 1 > 0 && x + 1 < WIDTH)
	{
		if (cell_state[(y - 1) * WIDTH + (x + 1)] == 1)
		{
			live_neighbors++;
		}
	}
	if (y - 1 > 0)
	{
		if (cell_state[(y - 1) * WIDTH + (x + 0)] == 1)
		{
			live_neighbors++;
		}
	}
	return live_neighbors;
}

//Cast final judgement on the cells.
void cell_inspector(int* cell_state, int* helper_cell_state, int y, int x, int live_neighbors)
{

	if (cell_state[y * WIDTH + x] == 1)						//Rules for living cells:
	{
		if (live_neighbors < 2)								//Underpopulation	
		{													//-- any live cell with < 2 live neighbors dies.
			helper_cell_state[y * WIDTH + x] = 0;
			//cout << "cell " << cell_number << " dies from 'underpopulation.'\n";
		}
		if (live_neighbors >= 2 && live_neighbors <= 3)		//Survival			
		{													//-- any live cell with 2 - 3 live neighbors survives to the next generation.
			helper_cell_state[y * WIDTH + x] = 1;
			//cout << "cell " << cell_number << " 'survives.'\n";
		}
		if (live_neighbors > 3)								//Overpopulation	
		{													//-- any live cell with > 3 live neighbors dies.
			helper_cell_state[y * WIDTH + x] = 0;
			//cout << "cell " << cell_number << " dies from 'overpopulation.'\n";
		}
	}
	if (cell_state[y * WIDTH + x] == 0)						//Rules for dead cells:
	{
		if (live_neighbors == 3)							//Reproduction	
		{													//-- any dead cell with exactly 3 neighbors becomes a live cell.
			helper_cell_state[y * WIDTH + x] = 1;
			//cout << "cell " << cell_number << " is 'born'.\n";
		}
	}
}

void array_alternator(int* cell_state, int* helper_cell_state)
{
	empty_grid(helper_cell_state);
	for (int y = 0; y < HEIGHT; y++)			//top to bottom
	{
		for (int x = 0; x < WIDTH; x++)			//left to right
		{
			int live_neighbors = scanning_for_life(cell_state, y, x);//"scanning for signs of life"
			cell_inspector(cell_state, helper_cell_state, y, x, live_neighbors);//"casting final judgement of cells"
			//cell_number++;
		}
	}
	display(helper_cell_state);
}