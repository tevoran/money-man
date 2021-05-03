#include "money_man.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

mm::object::object(mm::game *game, const char* path, const int x_in, const int y_in, const int w, const int h)
{
	m_game=game;
	m_w=w;
	m_h=h;
	x=x_in;
	y=y_in;
	SDL_Surface *tmp_surface=IMG_Load(path);
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

void mm::object::physics_update(const float time_secs)
{
	x=x+(x_speed)*time_secs;
	y=y+(y_speed)*time_secs;
	y_speed=y_speed+(m_game->gravity*time_secs);

	if((y+m_h)>m_game->res_y)
	{
		y=m_game->res_y-m_h;
	}
}