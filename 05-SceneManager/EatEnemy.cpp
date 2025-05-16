#define _USE_MATH_DEFINES  
#include <cmath>
#include "EatEnemy.h"

void EatEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
		left = x - 16/ 2;
		top = y - 16 / 2;
		right = left + 16;
		bottom = top + 16;
}


void EatEnemy::OnCollisionWith(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
}


