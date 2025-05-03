#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_PLANT 14000
#define PLANT_BBOX_WIDTH 16
#define PLANT_BBOX_HEIGHT 24

class CPlantEnemy : public CGameObject {
public:
    CPlantEnemy(float x, float y) : CGameObject(x, y) {}
    void Render();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    int IsBlocking() { return 1; }
    int IsCollidable() { return 1; }
};

