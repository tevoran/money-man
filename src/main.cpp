#include "money_man.hpp"
#include <iostream>
#include <chrono>
#include <ratio>
#include <cstdlib>
#include <ctime>

#define GRAVITY_CONSTANT 750
#define RES_X 1920
#define RES_Y 1080
#define FLOOR_OFFSET 64
#define DOLLAR_MAX_HEIGHT RES_Y-600

int main()
{
	SDL_Color text_color={255, 255, 255, 0};

	int floor_level=RES_Y-FLOOR_OFFSET;
	mm::game game(RES_X, RES_Y, GRAVITY_CONSTANT, floor_level, "../assets/font/Retroscape.ttf");
	mm::time frametime;

	mm::object player(&game, "../assets/player.png", RES_X/2, 0, 43, 127);
	mm::object floor(&game, "../assets/ground_tile.png", 0, RES_Y-FLOOR_OFFSET, 128, 64);
	mm::object dollar(&game, "../assets/dollar.png", 500, DOLLAR_MAX_HEIGHT, 45, 33);

	//text preparation

	int current_month=0;
	mm::text text_month[]=
	{
		mm::text(&game, "JANUARY", text_color),
		mm::text(&game, "FEBRUARY", text_color),
		mm::text(&game, "MARCH", text_color),
		mm::text(&game, "APRIL", text_color),
		mm::text(&game, "MAY", text_color),
		mm::text(&game, "JUNE", text_color),
		mm::text(&game, "JULY", text_color),
		mm::text(&game, "AUGUST", text_color),
		mm::text(&game, "SEPTEMBER", text_color),
		mm::text(&game, "OCTOBER", text_color),
		mm::text(&game, "NOVEMBER", text_color),
		mm::text(&game, "DECEMBER", text_color),
	};


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
			dollar.y=rand()%(400)+DOLLAR_MAX_HEIGHT;
			current_month++;
			if(current_month==12)
			{
				current_month=0;
			}
		}

		//Frame time management
		std::cout << 1/frametime.frametime_sec() << " FPS" << std::endl;

		//player physics
		player.physics_update(frametime.frametime_sec());

		//render
		text_month[current_month].render(RES_X-500,0);
		dollar.render();
		player.render();

		for(int i=0; i<((RES_X/floor.m_w)+1); i++)
		{
			floor.render(i*floor.m_w,RES_Y-FLOOR_OFFSET);
		}

		frametime.frametime_update_sec();
		game.update();

	}
	return 0;
}