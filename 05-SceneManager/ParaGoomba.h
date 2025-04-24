#pragma once
#include "Goomba.h"

#define PARAGOOMBA_GRAVITY 0.002f
#define PARAGOOMBA_WALKING_SPEED 0.05f
#define PARAGOOMBA_FLY_SPEED 0.03f
#define PARAGOOMBA_FLY_HEIGHT 30.0f
#define PARAGOOMBA_FLY_INTERVAL 2000 

#define PARAGOOMBA_BBOX_WIDTH 19
#define PARAGOOMBA_BBOX_HEIGHT 18

#define PARAGOOMBA_STATE_WALKING 100
#define PARAGOOMBA_STATE_FLYING 200

#define ID_ANI_PARAGOOMBA_WALKING 5002
#define ID_ANI_PARAGOOMBA_FLYING 5003

class CParaGoomba : public CGoomba
{
protected:
    ULONGLONG fly_start;
    float highest_y;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

    virtual void OnNoCollision(DWORD dt);
    virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
    CParaGoomba(float x, float y);
    virtual void SetState(int state);
};