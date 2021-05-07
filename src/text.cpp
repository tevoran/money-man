#include "money_man.hpp"

#include <iostream>

mm::text::text(mm::game *game, const char *text, SDL_Color& text_color)
{
	SDL_Surface *tmp_surface=TTF_RenderText_Solid(game->font, text, text_color);
	text_texture=SDL_CreateTextureFromSurface(game->renderer, tmp_surface);
	m_game=game;
	m_h=tmp_surface->h;
	m_w=tmp_surface->w;
	SDL_FreeSurface(tmp_surface);
}

void mm::text::render(int x, int y)
{
	SDL_Rect rect;
	rect.w=m_w;
	rect.h=m_h;
	rect.x=x;
	rect.y=y;
	SDL_RenderCopy(m_game->renderer, text_texture, NULL, &rect);
}