#include "money_man.hpp"
#include <ratio>
#include <chrono>
#include <iostream>

mm::time::time()
{
	clock_begin=std::chrono::steady_clock::now();
	clock_end=std::chrono::steady_clock::now();
	frametime=std::chrono::duration_cast<std::chrono::duration<float>>(clock_end-clock_begin);
}

float mm::time::frametime_update_sec()
{
	clock_end=std::chrono::steady_clock::now();
	frametime=std::chrono::duration_cast<std::chrono::duration<float>>(clock_end-clock_begin);
	clock_begin=clock_end;
	return frametime.count();
}

float mm::time::frametime_sec()
{
	return frametime.count();
}

void mm::time::keep_fps(int fps)
{
	float frametime_total=(float)1/(float)fps;
	float frametime_left=frametime_total-frametime.count();
	if(frametime_left<0)
	{
		return;
	}
	frametime_left=frametime_left*1000;
	SDL_Delay((uint32_t)frametime_left/2);
} 