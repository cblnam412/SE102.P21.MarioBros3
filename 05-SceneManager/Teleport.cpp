#define _USE_MATH_DEFINES  
#include <cmath>
#include "Teleport.h"

void Teleport::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - 16 / 2;
	top = y - 16 / 2;
	right = left + 16;
	bottom = top + 16;
}



