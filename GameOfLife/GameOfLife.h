#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#define CELLSIZE 5
//#define HEIGHT 30				//67
//#define WIDTH 40				//188

#include <iostream>
#include <random>	//"random" functions.
#include <chrono>	//harvest unique seed.
#include <thread>	//for pause function.

using namespace std;

//Game Of Life Functions.
void empty_grid(int width, int height, int* cell_state);
int randomNumber(int low, int high);
void seed_life(int width, int height, int* cell_state);
void display(int width, int height, int* cell_state, int generation);

int scanning_for_life(int width, int height, int* cell_state, int y, int x);
void cell_inspector(int width, int* cell_state, int* helper_cell_state, int y, int x, int live_neighbors);
void matrix_alternator(int width, int height, int* cell_state, int* helper_cell_state, int generation);

#endif