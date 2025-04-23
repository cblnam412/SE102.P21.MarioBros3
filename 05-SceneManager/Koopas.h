#pragma once
#include "GameObject.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.05f


#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 28

#define SHELL_BBOX_HEIGHT 16

#define KOOPAS_SHELL_TIMEOUT 4500

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_SHELL 200
#define KOOPAS_STATE_RELIVE 300
#define KOOPAS_STATE_ROTATE 400

#define ID_ANI_KOOPAS_WALKING 7000
#define ID_ANI_KOOPAS_SHELL 7001
#define ID_ANI_KOOPAS_RELIVE 7002
#define ID_ANI_KOOPAS_ROTATE 7003

class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG shell_start;

	void OnCollisionWithBrick(LPCOLLISIONEVENT e);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopas(float x, float y);
	virtual void SetState(int state);
};