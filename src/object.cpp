#include "money_man.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

mm::object::object(mm::game *game, const char* path, const int x_in, const int y_in, const int w, const int h)
{
	m_game=game;
	m_w=w;
	m_h=h;
	x=x_in;
	y=y_in;
	SDL_Surface *tmp_surface=IMG_Load(path);
	if(tmp_surface==NULL)
	{
		std::cout << "[WARNING]: sprite at " << path <<  " couldn't be loaded" << std::endl;
		exit(0);
	}
	texture=SDL_CreateTextureFromSurface(m_game->renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
}

void mm::object::render()
{
	SDL_Rect dst_rect;
	dst_rect.x=x;
	dst_rect.y=y;
	dst_rect.w=m_w;
	dst_rect.h=m_h;
	SDL_RenderCopy(m_game->renderer, texture, NULL, &dst_rect);
}

//render at a certain location
void mm::object::render(const int x_in, const int y_in)
{
	SDL_Rect dst_rect;
	dst_rect.x=x_in;
	dst_rect.y=y_in;
	dst_rect.w=m_w;
	dst_rect.h=m_h;
	SDL_RenderCopy(m_game->renderer, texture, NULL, &dst_rect);
}

void mm::object::render_frame(const int num_frame,const int x_in, const int y_in)
{
	SDL_Rect src_rect;
	src_rect.x=m_w*num_frame;
	src_rect.y=0;
	src_rect.w=m_w;
	src_rect.h=m_h;
	SDL_Rect dst_rect;
	dst_rect.x=x_in;
	dst_rect.y=y_in;
	dst_rect.w=m_w;
	dst_rect.h=m_h;
	SDL_RenderCopy(m_game->renderer, texture, &src_rect, &dst_rect);
}

void mm::object::physics_update(const float time_secs, const uint32_t flags)
{
	//location update
	x=x+(x_speed)*time_secs;
	y=y+(y_speed)*time_secs;

	//bumping into screen borders
	if(flags & SCREEN_COLLISION_FLAG)
	{
		if(x<0)
		{
			x=0;
			x_speed=-x_speed;
		}

		if((x+m_w)>m_game->res_x)
		{
			x=m_game->res_x-m_w;
			x_speed=-x_speed;
		}
	}

	//gravity
	if(flags & GRAVITY_FLAG)
	{
		y_speed=y_speed+(m_game->gravity*time_secs);

		if((y+m_h) > m_game->floor_y)
		{
			x_speed=0;
			y_speed=0;
			y=m_game->floor_y-m_h;
		}
	}
}