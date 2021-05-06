#include "money_man.hpp"
#include <iostream>
#include <chrono>
#include <ratio>
#include <cstdlib>
#include <ctime>

#define GRAVITY_CONSTANT 750
#define RES_X 1366
#define RES_Y 766
#define FLOOR_OFFSET 64
#define DOLLAR_MAX_HEIGHT RES_Y-600

int main()
{
	int floor_level=RES_Y-FLOOR_OFFSET;
	mm::game game(RES_X, RES_Y, GRAVITY_CONSTANT, floor_level);
	mm::time frametime;

	mm::object player(&game, "../assets/player.png", RES_X/2, 0, 43, 127);
	mm::object floor(&game, "../assets/ground_tile.png", 0, RES_Y-FLOOR_OFFSET, 64, 64);
	mm::object dollar(&game, "../assets/dollar.png", 500, DOLLAR_MAX_HEIGHT, 64, 64);

	//initializing random seed
	srand(time(NULL));

	//main loop
	bool quit=false;
	while(!quit)
	{
		mm::handling_input(game, quit, player);

		//player hits dollars
		if(mm::is_colliding(player, dollar)==true)
		{
			dollar.x=rand()%(RES_X-dollar.m_w);
		}

		//Frame time management
		std::cout << 1/frametime.frametime_sec() << " FPS" << std::endl;

		//player physics
		player.physics_update(frametime.frametime_sec());

		//render
		dollar.render();
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