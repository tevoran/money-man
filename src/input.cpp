#include "money_man.hpp"

void mm::handling_input(mm::game& game, bool& quit, mm::object& player)
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
}