#include "money_man.hpp"
#include <iostream>


int main()
{
	mm::game game;

	//main loop
	bool quit=false;
	while(!quit)
	{

		//input queue
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if(event.type==SDL_QUIT)
			{
				quit=true;
			}
		}

		game.update();
	}
	return 0;
}