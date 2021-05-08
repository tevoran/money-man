#include "money_man.hpp"

void mm::player_animate(mm::object& player, mm::time& time)
{
	if(player.y==RES_Y-FLOOR_OFFSET-player.m_h)
	{
		mm::player_animation_idle(player, time);
	}
	if(player.y<RES_Y-FLOOR_OFFSET-player.m_h)
	{
		mm::player_animation_jump(player, time);
	}
}

void mm::player_animation_idle(mm::object& player, mm::time& time)
{
	static float idle_time=0;
	if((player.y==RES_Y-FLOOR_OFFSET-player.m_h) && player.x_speed==0)
	{
		idle_time+=time.frametime_sec();
	}
	else
	{
		idle_time=0;
	}
	if(idle_time>0.5)
	{
		player.render_frame(1, player.x, player.y);
	}
	else
	{
		player.render_frame(0, player.x, player.y);
	}
	if(idle_time>1)
	{
		idle_time=0;
	}
}

void mm::player_animation_jump(mm::object& player, mm::time& time)
{
	if(player.y!=RES_Y-FLOOR_OFFSET-player.m_h)
	{
		player.render_frame(2, player.x, player.y);
	}
}