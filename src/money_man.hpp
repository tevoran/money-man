#pragma once
#include <SDL2/SDL.h>

namespace mm
{
	class game
	{
	private:
		SDL_Window *window=NULL;
	public:
		int res_x=0;
		int res_y=0;
		float gravity=0;

		SDL_Renderer *renderer=NULL;
		game(const int res_x_in, const int res_y_in, const float gravity_in);
		~game();
		void update();
	};

	class object
	{
	private:
		SDL_Texture *texture=NULL;
		mm::game *m_game=NULL;

		float x_speed=0;
		float y_speed=0;

		int m_w=0;
		int m_h=0;

	public:
		float x=0;
		float y=0;

		object(mm::game *game, const char* path, const int x_in, const int y_in, const int w, const int h);
		void render();
		void physics_update(const float time_secs);
	};
}