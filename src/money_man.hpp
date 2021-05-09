#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <chrono>
#include <ratio>


#define GRAVITY_CONSTANT 750
#define RES_X 1920
#define RES_Y 1080
#define FLOOR_OFFSET 64
#define DOLLAR_MAX_HEIGHT RES_Y-600
#define NUM_CLOUDS 20
#define TARGET_FPS 60


#define GRAVITY_FLAG 0x01
#define SCREEN_COLLISION_FLAG 0x02

namespace mm
{
	class time
	{
	private:
		std::chrono::steady_clock::time_point clock_begin;
		std::chrono::steady_clock::time_point clock_end;
		std::chrono::duration<float> frametime;
	public:
		time();
		float frametime_update_sec();
		float frametime_sec();
		void keep_fps(int fps);
	};

	class game
	{
	private:
		SDL_Window *window=NULL;

	public:
		int res_x=0;
		int res_y=0;
		float gravity=0;
		float floor_y=0;

		TTF_Font *font=NULL;

		SDL_Renderer *renderer=NULL;
		game(const int res_x_in, const int res_y_in, const float gravity_in, const int floor_level, const char *font_path);
		~game();
		void update();
	};

	class object
	{
	private:
		SDL_Texture *texture=NULL;
		mm::game *m_game=NULL;

	public:
		float x_speed=0;
		float y_speed=0;

		float x=0;
		float y=0;

		int m_w=0;
		int m_h=0;

		object(mm::game *game, const char* path, const int x_in, const int y_in, const int w, const int h);
		void render();
		void render(const int x_in, const int y_in);
		void physics_update(const float time_secs, const uint32_t flags);
		void render_frame(const int num_frame,const int x_in, const int y_in);
	};

	class text
	{
	private:
		SDL_Texture *text_texture=NULL;
		mm::game *m_game=NULL;
		int m_w;
		int m_h;
	public:
		text(mm::game *game, const char *text, SDL_Color& text_color);
		void render(int x, int y);
	};

	void handling_input(mm::game& game, bool& quit, mm::object& player, bool& intro);
	bool is_colliding(mm::object& a, mm::object& b);

	void player_animate(mm::object& player, mm::time& time);
	void player_animation_idle(mm::object& player, mm::time& time);
	void player_animation_jump(mm::object& player, mm::time& time);
}