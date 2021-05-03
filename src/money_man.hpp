#pragma once
#include <SDL2/SDL.h>

namespace mm
{
	class game
	{
	private:
		SDL_Window *window=NULL;
		SDL_Renderer *renderer=NULL;
	public:
		game();
		void update();
	};
}