#include "money_man.hpp"
#include <iostream>
#include <chrono>
#include <ratio>


#define GRAVITY_CONSTANT 750
#define RES_X 1366
#define RES_Y 766
#define FLOOR_OFFSET 64

int main()
{
	int floor_level=RES_Y-FLOOR_OFFSET;
	mm::game game(RES_X, RES_Y, GRAVITY_CONSTANT, floor_level);
	mm::time frametime;

	mm::object player(&game, "../assets/player.png", RES_X/2, 0, 43, 127);
	mm::object floor(&game, "../assets/ground_tile.png", 0, RES_Y-FLOOR_OFFSET, 64, 64);

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

		if(keyboard_state[SDL_SCANCODE_SPACE] && (player.y+127) == game.floor_y) //jump
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
		std::cout << 1/frametime.frametime_sec() << " FPS" << std::endl;

		//player physics
		player.physics_update(frametime.frametime_sec());

		//render
		player.render();
		for(int i=0; i<((RES_X/64)+1); i++)
		{
			floor.render(i*64,RES_Y-FLOOR_OFFSET);
		}

		frametime.frametime_update_sec();
		game.update();

	}
	return 0;
}