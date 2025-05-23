#pragma once
#include "GameObject.h"

#define BULLET_VX 0.06f
#define BULLET_VY 0.03f

#define PLANT_BULLET_BBOX_WIDTH 8
#define PLANT_BULLET_BBOX_HEIGHT 8

#define ID_ANI_BULLET 15000

class CBullet : public CGameObject {

public:
    CBullet(float x, float y, float vx, float vy) : CGameObject(x, y) {
        this->vx = vx;
        this->vy = vy;
        IsWaitable = true;
    }
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b);

    void OnCollisionWith(LPCOLLISIONEVENT e);
    void OnNoCollision(DWORD dt);
    void SetSpeed(float vx, float vy) {
        this->vx = vx;
        this->vy = vy;
    }
    int IsBlocking() override { return 0; }
};