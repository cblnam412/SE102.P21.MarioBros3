#pragma once
#include "GameObject.h"

#define LEAF_BBOX_WIDTH  16
#define LEAF_BBOX_HEIGHT 16

#define LEAF_SPEED_Y     0.02f

#define ID_ANI_LEAF      30001

class CLeaf : public CGameObject
{
protected:
    float ay; 

public:
    CLeaf();

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
    void Render() override;
    void OnNoCollision(DWORD dt) override;
    void OnCollisionWith(LPCOLLISIONEVENT e) override {}

    void GetBoundingBox(float& l, float& t, float& r, float& b) override;
};
