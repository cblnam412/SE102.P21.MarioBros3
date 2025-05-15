#define _USE_MATH_DEFINES  
#include <cmath>
#include "Koopas.h"
#include "Brick.h"

CKoopas::CKoopas(float x, float y, int type) : CGameObject(x, y)
{
	this->type = type;
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	shell_start = -1;
	SetState(KOOPAS_STATE_WALKING_LEFT);
}


void CKoopas::setVX(float vx) {
	this->vx = vx;
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_RELIVE || state == KOOPAS_STATE_ROTATE)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - SHELL_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + SHELL_BBOX_HEIGHT;
	}
	else if (state == KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;

	if (e->obj->IsBlocking())
	{
		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			if (state == KOOPAS_STATE_WALKING_LEFT)
				SetState(KOOPAS_STATE_WALKING_RIGHT);
			else if (state == KOOPAS_STATE_WALKING_RIGHT)
				SetState(KOOPAS_STATE_WALKING_LEFT);
			else
				vx = -vx;
		}
	}

	if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
}

void CKoopas::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	if (state == KOOPAS_STATE_ROTATE)
	{
		if (e->nx != 0)
			e->obj->Delete();
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;


	if (state == KOOPAS_STATE_SHELL)
	{
		DWORD shell_time = GetTickCount64() - shell_start;

		if (shell_time > KOOPAS_SHELL_TIMEOUT)
		{
			DWORD shake_duration = 1500;
			DWORD shake_time = shell_time - KOOPAS_SHELL_TIMEOUT;

			if (shake_time <= shake_duration)
			{
				float frequency = 10.0f;
				float shake_speed = 0.05f;
				vx = shake_speed * sin(2 * M_PI * frequency * shake_time / 1000.0f);
			}
			else
			{
				SetState(KOOPAS_STATE_RELIVE);
			}
		}
	}

	if (state == KOOPAS_STATE_RELIVE)
	{
		DWORD relive_time = GetTickCount64() - shell_start;
		const DWORD shake_duration = 1000;

		if (relive_time <= shake_duration)
		{
			const float frequency = 12.0f;
			const float shake_speed = 0.08f;
			vx = shake_speed * sin(2 * M_PI * frequency * relive_time / 1000.0f);
		}
		else
		{
			y -= (KOOPAS_BBOX_HEIGHT - SHELL_BBOX_HEIGHT) / 2;
			SetState(KOOPAS_STATE_WALKING_LEFT);
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopas::Render()
{
	int aniId = getAni();

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case KOOPAS_STATE_SHELL:
		shell_start = GetTickCount64();
		vx = 0;
		break;

	case KOOPAS_STATE_WALKING_LEFT:
		vx = -KOOPAS_WALKING_SPEED;
		ay = KOOPAS_GRAVITY;
		break;

	case KOOPAS_STATE_WALKING_RIGHT:
		vx = KOOPAS_WALKING_SPEED;
		break;

	case KOOPAS_STATE_RELIVE:
		shell_start = GetTickCount64();
		vx = 0;
		break;

	case KOOPAS_STATE_ROTATE:
		setVX(-KOOPAS_ROTATE_SPEED);
		break;
	}
}
