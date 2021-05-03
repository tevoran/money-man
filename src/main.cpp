#include "money_man.hpp"
#include <iostream>


int main()
{
	mm::game game;

	mm::object player(game, "../assets/player.png");

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
		player.render(50,50,200,200);
		game.update();
	}
	return 0;
}