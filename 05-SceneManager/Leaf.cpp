#include "Leaf.h"
#include "Platform.h"

#define LEAF_FALL_SPEED 0.0001f
#define OUT_BRICK 0.13f
#define LEAF_SPEED 0.04f

CLeaf::CLeaf(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = LEAF_FALL_SPEED;
	this->vx = 0; // Không lượn ngang
	this->vy = -OUT_BRICK;
	isOnPlatForm = false;
	SetState(LEAF_STATE_FALL);
}

CLeaf::CLeaf(float x, float y, int state)
{
	this->x = x;
	this->y = y;
	this->ax = 0;
	this->vx = 0;
	this->state = state;
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!checkObjectInCamera(this)) return;

	if (isOnPlatForm) {
		vy = 0;
		ay = 0;
		vx = 0;
	}
	else {
		if (vy < MAX_VY) {
			vy += ay * dt;
		}
		else vy = ay * dt;

		vx = 0; // Không cho di chuyển ngang
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking() && !e->obj->IsPlatform()) return;
	if (dynamic_cast<CLeaf*>(e->obj)) return;

	if (e->ny != 0)
	{
		isOnPlatForm = true;
		vy = 0;
		vx = 0;
	}
	else if (dynamic_cast<CPlatform*>(e->obj))
		OnCollisionWithPlatForm(e);
}

void CLeaf::OnCollisionWithPlatForm(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	if (platform->IsBlocking()) {}
	else if (e->ny < 0) {
		SetY(platform->GetY() - LEAF_BBOX_HEIGHT);
		isOnPlatForm = true;
	}
}

void CLeaf::Render()
{
	if (!checkObjectInCamera(this)) return;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_LEAF_LEFT)->Render(x, y); // Dù không lượn, vẫn dùng 1 hướng

	//RenderBoundingBox();
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CLeaf::SetState(int state)
{
	switch (state)
	{
	case LEAF_STATE_FALL:
		ax = 0;
		vx = 0;
		break;
	}

	CGameObject::SetState(state);
}
