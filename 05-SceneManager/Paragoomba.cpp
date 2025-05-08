#include "Paragoomba.h"
#include "Mario.h"

CParagoomba::CParagoomba(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = PARAGOOMBA_GRAVITY;
	jump_count = 0;
	die_start = -1;
	SetState(PARAGOOMBA_STATE_WALKING);
}

void CParagoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == PARAGOOMBA_STATE_DIE)
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y - PARAGOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + PARAGOOMBA_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y - PARAGOOMBA_BBOX_HEIGHT / 2;
		right = left + PARAGOOMBA_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT;
	}
}

void CParagoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CParagoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CParagoomba*>(e->obj)) return;

	if (dynamic_cast<CMario*>(e->obj)) {
		if (e->ny > 0 && state != PARAGOOMBA_STATE_DIE) {
			SetState(PARAGOOMBA_STATE_DIE);
			return;
		}
	}

	if (e->ny != 0)
	{
		vy = 0;

		if (state == PARAGOOMBA_STATE_WALKING)
		{
			if (jump_count < PARAGOOMBA_JUMP_COUNT)
			{
				vy = PARAGOOMBA_JUMP_VY;
				jump_count++;
			}
			else
			{
				vy = PARAGOOMBA_HIGH_JUMP_VY;
				jump_count = 0;
				vx = -vx; // Quay đầu
			}
		}
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CParagoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == PARAGOOMBA_STATE_DIE) && (GetTickCount64() - die_start > PARAGOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CParagoomba::Render()
{
	int aniId = ID_ANI_PARAGOOMBA_WALKING;
	if (state == PARAGOOMBA_STATE_DIE)
		aniId = ID_ANI_PARAGOOMBA_DIE;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CParagoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PARAGOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (PARAGOOMBA_BBOX_HEIGHT - PARAGOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = -0.03f;
		break;

	case PARAGOOMBA_STATE_WALKING:
		vx = -PARAGOOMBA_WALKING_SPEED;
		ay = PARAGOOMBA_GRAVITY;
		break;
	}
}
