#include "BrickQuestion.h"

void CBrickQuestion::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICKQUESTION)->Render(x, y);
	//RenderBoundingBox();
}

void CBrickQuestion::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICKQUESTION_BBOX_WIDTH / 2;
	t = y - BRICKQUESTION_BBOX_HEIGHT / 2;
	r = l + BRICKQUESTION_BBOX_WIDTH;
	b = t + BRICKQUESTION_BBOX_HEIGHT;
}