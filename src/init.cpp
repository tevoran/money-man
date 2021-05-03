#include "money_man.hpp"

#include <SDL2/SDL.h>
#include <iostream>

mm::game::~game()
{
	SDL_Quit();
}

mm::game::game(const int res_x_in, const int res_y_in, const float gravity_in, const int floor_level)
{
	res_x=res_x_in;
	res_y=res_y_in;
	gravity=gravity_in;
	floor_y=(float)floor_level;

	SDL_Init(SDL_INIT_EVERYTHING);
	window=SDL_CreateWindow("Money Man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, res_x, res_y, 0);
	renderer=SDL_CreateRenderer(window, -1, 0);
}