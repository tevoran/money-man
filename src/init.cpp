#include "money_man.hpp"

#include <SDL2/SDL.h>
#include <iostream>

mm::game::game()
{
	window=SDL_CreateWindow("Money Man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	renderer=SDL_CreateRenderer(window, -1, 0);
}