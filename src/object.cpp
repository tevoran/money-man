#include "money_man.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

mm::object::object(mm::game& game, const char* path)
{
	renderer=game.renderer;
	SDL_Surface *tmp_surface=IMG_Load(path);
	texture=SDL_CreateTextureFromSurface(renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
}

void mm::object::render(int x, int y, int w, int h)
{
	SDL_Rect dst_rect;
	dst_rect.x=x;
	dst_rect.y=y;
	dst_rect.w=w;
	dst_rect.h=h;
	SDL_RenderCopy(renderer, texture, NULL, &dst_rect);
}