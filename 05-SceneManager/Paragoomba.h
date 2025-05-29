#pragma once
#include "GameObject.h"

#define PARAGOOMBA_GRAVITY 0.002f
#define PARAGOOMBA_WALKING_SPEED 0.05f

#define PARAGOOMBA_BBOX_WIDTH 16
#define PARAGOOMBA_BBOX_HEIGHT 16
#define PARAGOOMBA_BBOX_HEIGHT_DIE 7

#define PARAGOOMBA_STATE_WALKING 100
#define PARAGOOMBA_STATE_DIE 200
#define PARAGOOMBA_STATE_WALK_NOFLY 300

#define PARAGOOMBA_JUMP_VY -0.2f
#define PARAGOOMBA_HIGH_JUMP_VY -0.4f
#define PARAGOOMBA_JUMP_COUNT 3

#define PARAGOOMBA_DIE_TIMEOUT 500

#define ID_ANI_PARAGOOMBA_WALKING 5002
#define ID_ANI_PARAGOOMBA_DIE 5004
#define ID_ANI_PARAGOOMBA_WALK_NOFLY 5003

class CParagoomba : public CGameObject
{
protected:
	float ax;
	float ay;

	int jump_count;
	ULONGLONG die_start;

    float start_walk_x = x; 
    const float MAX_WALK_DISTANCE = 48.0f;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CParagoomba(float x, float y);
	virtual void SetState(int state);
	float GetX() { return x; }
	float GetY() { return y; }
};
