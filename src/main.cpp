#include "money_man.hpp"
#include <iostream>
#include <ctime>


#define GRAVITY_CONSTANT 750
#define RES_X 1366
#define RES_Y 766
#define FLOOR_OFFSET 64
#define FRICTION 0.01

int main()
{
	int floor_level=RES_Y-FLOOR_OFFSET;
	mm::game game(RES_X, RES_Y, GRAVITY_CONSTANT, floor_level);

	mm::object player(&game, "../assets/player.png", RES_X/2, 0, 43, 127);
	mm::object floor(&game, "../assets/ground_tile.png", 0, RES_Y-FLOOR_OFFSET, 64, 64);

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

		}
		//keyboard
		const uint8_t *keyboard_state=SDL_GetKeyboardState(NULL);
		if(keyboard_state[SDL_SCANCODE_ESCAPE]) //ending game
		{
			quit=true;
		}

		if(keyboard_state[SDL_SCANCODE_SPACE]) //jump
		{
			player.y_speed=-800;
		}

		if(keyboard_state[SDL_SCANCODE_A]) //moving left
		{
			player.x_speed=-400;
		}

		if(keyboard_state[SDL_SCANCODE_D]) //moving right
		{
			player.x_speed=400;
		}

		if(keyboard_state[SDL_SCANCODE_A] && keyboard_state[SDL_SCANCODE_D])
		{
			player.x_speed=0;
		}

		//Frame time management
		clock_end=std::clock();
		frametime_s=(float)(clock_end-clock_begin)/CLOCKS_PER_SEC;
		clock_begin=clock_end;
		std::cout << 1/frametime_s << " FPS"<< std::endl;
		
		//player physics
		player.physics_update(FRICTION, frametime_s);

		//render
		player.render();
		for(int i=0; i<((RES_X/64)+1); i++)
		{
			floor.render(i*64,RES_Y-FLOOR_OFFSET);
		}
		game.update();

	}
	return 0;
}