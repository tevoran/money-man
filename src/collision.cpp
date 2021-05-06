#include "money_man.hpp"

//rectangle collision
bool mm::is_colliding(mm::object& a, mm::object& b)
{
	if(	a.x+a.m_w > b.x &&
		a.x < b.x+b.m_w &&
		a.y+a.m_h > b.y &&
		a.y < b.y+b.m_h)
	{
		return true;
	}
	else
	{
		return false;
	}
}