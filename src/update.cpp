#include "money_man.hpp"
#include <SDL2/SDL.h>

void mm::game::update()
{
	SDL_SetRenderDrawColor(renderer, 0, 187, 255, 0); //Skylike color
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}