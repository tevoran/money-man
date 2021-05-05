#include "money_man.hpp"
#include <ratio>
#include <chrono>

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