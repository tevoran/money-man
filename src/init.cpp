#include "money_man.hpp"

#include <SDL2/SDL.h>
#include <iostream>

int RES_Y=0;
int RES_X=0;

mm::game::~game()
{
	TTF_Quit();
	SDL_Quit();
}

mm::game::game(const float gravity_in, int& floor_level, const char *font_path)
{
	gravity=gravity_in;

	SDL_Init(SDL_INIT_EVERYTHING);

	//getting system's resolution
	SDL_DisplayMode vinfo;
	if(SDL_GetDesktopDisplayMode(0, &vinfo)!=0)
	{
		std::cout << "[WARNING]: Couldn't get desktop resolution" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		exit(0);
	}
	floor_level=vinfo.h-FLOOR_OFFSET;
	floor_y=(float)floor_level;

	RES_X=vinfo.w;
	RES_Y=vinfo.h;
	res_x=RES_X;
	res_y=RES_Y;

	window=SDL_CreateWindow("Money Man", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, res_x, res_y, SDL_WINDOW_FULLSCREEN);
	if(window==NULL)
	{
		std::cout << "SDL can't create a window" << std::endl;
		exit(0);
	}
	renderer=SDL_CreateRenderer(window, -1, 0);
	if(renderer==NULL)
	{
		std::cout << "SDL can't create a renderer" << std::endl;
		exit(0);
	}
	std::cout << "TTF Init: " << TTF_Init() << std::endl;
	font=TTF_OpenFont(font_path, (int)(0.04*(float)RES_Y));
	if(font==NULL)
	{
		std::cout << "[WARNING]: Font wasn't found at: " << font_path << std::endl;
		std::cout << "ERROR: " << TTF_GetError() << std::endl;
		exit(0);
	}
}