#include "money_man.hpp"
#include <iostream>
#include <chrono>
#include <ratio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cstdio>
#include <SDL2/SDL.h>

#undef main


int main(int argc, char *argv[])
{

	SDL_Color text_color={45, 44, 44, 0};

	int floor_level;
	std::cout << "init game base: " << std::endl;
	mm::game game(GRAVITY_CONSTANT, floor_level, "../assets/font/Retroscape.ttf");
	srand(time(NULL)); 	//initializing random seed
	mm::time frametime;


	//loading assets
	std::cout << "loading assets:" << std::endl;
	mm::object player(&game, "../assets/player_anim.png", RES_X/2, 0, 43, 127);
	mm::object floor(&game, "../assets/ground_tile.png", 0, RES_Y-FLOOR_OFFSET, 128, 64);
	mm::object dollar(&game, "../assets/dollar.png", 500, DOLLAR_MAX_HEIGHT, (int)(0.025*(float)RES_X), (int)(0.036*(float)RES_Y));
	mm::object background(&game, "../assets/background.png", 0,0, RES_X, RES_Y);

	std::vector<mm::object> cloud;
	for(int i=0; i<NUM_CLOUDS; i++)
	{
		cloud.push_back(mm::object(&game, "../assets/cloud1.png", rand()%RES_X, rand()%(int)(0.3*(float)RES_Y), (int)(0.0667*(float)RES_X), (int)(0.059*(float)RES_Y)));
			cloud[i].x_speed=rand()%((int)(0.021*(float)RES_X))+(int)(0.005*(float)RES_X);
	}

	//text preparation
	text_color={228,225,228,0};

	mm::text intro_text1(&game, "WELCOME TO MONEY MAN", text_color);
	mm::text intro_text2(&game, "YOU JUST GOT YOUR FIRST JOB", text_color);
	mm::text intro_text3(&game, "BUT DO YOU HAVE WHAT IT TAKES", text_color);
	mm::text intro_text4(&game, "TO WORK UNTIL RETIREMENT?", text_color);
	mm::text intro_text5(&game, "PRESS <SPACE> TO START", text_color);

	mm::text end_of_game1(&game, "CONGRATULATIONS!", text_color);
	mm::text end_of_game2(&game, "YOU ARE NOW RETIRED", text_color);
	mm::text end_of_game3(&game, "BUT SADLY YOU DIED TWO YEARS", text_color);
	mm::text end_of_game4(&game, "LATER BECAUSE OF CANCER", text_color);

	text_color={45,44,44,0};
	char age[]="AGE: XX YEARS";
	std::vector<mm::text> text_age;
	int current_age=0;

	for(int i=18; i<=65; i++)
	{
		sprintf(age+5, "%i YEARS", i);
		text_age.push_back(mm::text(&game, age, text_color));
		std::cout << age << std::endl;
	}


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

	//main loop
	bool intro=true;
	bool quit=false;
	while(!quit)
	{
		mm::handling_input(game, quit, player, intro);
		if(intro==false)
		{

			//player hits dollars
			if(mm::is_colliding(player, dollar)==true)
			{
				dollar.x=rand()%(RES_X-dollar.m_w);
				dollar.y=rand()%(400)+DOLLAR_MAX_HEIGHT;
				current_month++;
				if(current_month==12)
				{
					current_month=0;
					current_age++;
				}
			}
		}

			//Frame time management
			std::cout << "Frame calculation time: " << frametime.frametime_sec()*1000 << " ms" << std::endl;

			//render
			//clouds
			for(int i=0; i<NUM_CLOUDS; i++)
			{
				cloud[i].render();
				cloud[i].physics_update(frametime.frametime_sec(), 0);
				if(cloud[i].x>RES_X)
				{
					cloud[i].x=-cloud[i].m_w;
				}
			}

			background.render();
			dollar.render();

			//player animations
			mm::player_animate(player, frametime);

			for(int i=0; i<((RES_X/floor.m_w)+1); i++)
			{
				floor.render(i*floor.m_w,RES_Y-FLOOR_OFFSET);
			}

			if(current_age<=47)
			{
				text_age[current_age].render(0,0);
				text_month[current_month].render(RES_X-500,0);
			}
			//end of game
			if(current_age>47)
			{
				end_of_game1.render((int)(0.15*(float)RES_X),(int)(0.35*(float)RES_Y));
				end_of_game2.render((int)(0.15*(float)RES_X),(int)(0.45*(float)RES_Y));	
				end_of_game3.render((int)(0.15*(float)RES_X),(int)(0.51*(float)RES_Y));
				end_of_game4.render((int)(0.15*(float)RES_X),(int)(0.57*(float)RES_Y));	
			}

		if(intro==true)
		{
			intro_text1.render((int)(0.15*(float)RES_X),(int)(0.35*(float)RES_Y));
			intro_text2.render((int)(0.15*(float)RES_X),(int)(0.45*(float)RES_Y));	
			intro_text3.render((int)(0.15*(float)RES_X),(int)(0.51*(float)RES_Y));
			intro_text4.render((int)(0.15*(float)RES_X),(int)(0.57*(float)RES_Y));
			intro_text5.render((int)(0.15*(float)RES_X),(int)(0.65*(float)RES_Y));
		}

			//player physics
			player.physics_update(frametime.frametime_sec(), GRAVITY_FLAG | SCREEN_COLLISION_FLAG);
			frametime.keep_fps(TARGET_FPS);
			frametime.frametime_update_sec();

			game.update();

	}
	return 0;
}