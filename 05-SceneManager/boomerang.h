#pragma once
#include "GameObject.h"

#define BMR_BBOX_WIDTH 16
#define BMR_BBOX_HEIGHT 16

#define BOOMERANG_SPEED_X 0.1f
#define BOOMERANG_SPEED_Y 0.05f
#define BOOMERANG_GRAVITY 0.00001f

#define ID_ANI_BOOMERANG    13201

class CBoomerang : public CGameObject
{
private:
    int dir;
    int phase;
    ULONGLONG phase_start;

public:
    CBoomerang(float x, float y, int dir);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};