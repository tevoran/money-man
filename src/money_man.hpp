#pragma once
#include <SDL2/SDL.h>

namespace mm
{
	class game
	{
	private:
		SDL_Window *window=NULL;
	public:
		SDL_Renderer *renderer=NULL;
		game();
		~game();
		void update();
	};

	class object
	{
	private:
		SDL_Texture *texture=NULL;
		SDL_Renderer *renderer=NULL;
	public:
		object(mm::game& game, const char* path);
		void render(int x, int y, int w, int h);
	};
}