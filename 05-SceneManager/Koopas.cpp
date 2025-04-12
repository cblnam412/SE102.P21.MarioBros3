#define _USE_MATH_DEFINES  
#include <cmath>
#include "Koopas.h"


CKoopas::CKoopas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	shell_start = -1;
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_SHELL)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - SHELL_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + SHELL_BBOX_HEIGHT;
	}
	else if (state == KOOPAS_STATE_WALKING)
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

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
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
				if (state == KOOPAS_STATE_SHELL)
				{
					SetState(KOOPAS_STATE_RELIVE);
				}
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
			SetState(KOOPAS_STATE_WALKING);
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING;
	if (state == KOOPAS_STATE_SHELL)
	{
		aniId = ID_ANI_KOOPAS_SHELL;
	}
	else if (state == KOOPAS_STATE_RELIVE) {
		aniId = ID_ANI_KOOPAS_RELIVE;
	}

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
		y += (KOOPAS_BBOX_HEIGHT - SHELL_BBOX_HEIGHT) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		y -= (KOOPAS_BBOX_HEIGHT - SHELL_BBOX_HEIGHT) / 2;
		ay = KOOPAS_GRAVITY;
		break;
	case KOOPAS_STATE_RELIVE:
		shell_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	}
}
