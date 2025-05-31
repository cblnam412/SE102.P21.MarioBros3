#include "Lift.h"

void CLift::Render() {
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_SPRITES_LIFT)->Draw(x, y);
}

void CLift::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

    prevX = x; 
    prevY = y;

    //if (isDropping) 
    {
        y += vy * dt;
        x += vx * dt;
    }

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLift::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LIFT_BBOX_WIDTH / 2;
	t = y - LIFT_BBOX_HEIGHT / 2;
	r = l + LIFT_BBOX_WIDTH;
	b = t + LIFT_BBOX_HEIGHT;
}

int CLift::IsDirectionColliable(float nx, float ny) {
	if (ny < 0.0f) {
		return 1;
	}
	return 0;
}

void CLift::swapVXY() {
    if (!isDropping) {
        vx = 0;
        vy = LIFT_SPEED_DROP;
        isDropping = true;
    }
}