#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#define HEIGHT 30				//67
#define WIDTH 40				//188

#include <iostream>
#include <SDL3/SDL.h>
#include <random>	//"random" functions.
#include <chrono>	//harvest unique seed.
#include <thread>	//for pause function.

using namespace std;

//Game Of Life Functions.
void start_SDL3(SDL_Window* window, SDL_Renderer* renderer);

void empty_grid(int* cell_state);
int randomNumber(int low, int high);
void seed_life(int* cell_state);
void display(int* cell_state);

int scanning_for_life(int* cell_state, int y, int x);
void cell_inspector(int* cell_state, int* helper_cell_state, int y, int x, int live_neighbors);
void array_alternator(int* cell_state, int* helper_cell_state);

#endif