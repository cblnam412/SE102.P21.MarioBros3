#include "Leaf.h"

#define LEAF_SPEED 0.00005f


void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay;
	if (vy >= 0.09) {
		ay = -ay;
		vx = -vx;
	}
	else if (vy <= 0.0) {
		ay = -ay;
		vx = -vx;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLeaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_LEAF)->Render(x, y);
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}