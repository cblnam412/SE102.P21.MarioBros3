#define _USE_MATH_DEFINES  
#include <cmath>
#include "Teleport.h"

void Teleport::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    const float TELEPORT_WIDTH = 25.0f;
    const float TELEPORT_HEIGHT = 30.0f;

    left = x - TELEPORT_WIDTH / 2;
    top = y - TELEPORT_HEIGHT / 2;
    right = left + TELEPORT_WIDTH;
    bottom = top + TELEPORT_HEIGHT;
}



