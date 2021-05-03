#include "money_man.hpp"
#include <iostream>
#include <ctime>


#define GRAVITY_CONSTANT 500
int main()
{
	mm::game game(1366, 768, GRAVITY_CONSTANT);

	mm::object player(&game, "../assets/player.png", 450, 50, 128, 128);

	std::clock_t clock_begin=std::clock();
	std::clock_t clock_end=std::clock();
	float frametime_s;
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

			//keyboard
			const uint8_t *keyboard_state=SDL_GetKeyboardState(NULL);
		}

		//player physics
		player.physics_update(frametime_s);
		player.render();
		game.update();

		clock_end=std::clock();
		frametime_s=(float)(clock_end-clock_begin)/CLOCKS_PER_SEC;
		clock_begin=clock_end;

		std::cout << 1/frametime_s << " FPS"<< std::endl;
	}
	return 0;
}