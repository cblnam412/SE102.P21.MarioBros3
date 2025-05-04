#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Bullet.h"

#define ID_ANI_PLANT 14000
#define PLANT_BBOX_WIDTH 16
#define PLANT_BBOX_HEIGHT 24

#define PLANT_BULLET_FIRE_INTERVAL 3000

class CPlantEnemy : public CGameObject {
protected:
    ULONGLONG lastFireTime = 0;
public:
    CPlantEnemy(float x, float y) : CGameObject(x, y) {}
    void Render() override;
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void GetBoundingBox(float& l, float& t, float& r, float& b);
   
    int IsBlocking() override { return 0; }
    int IsCollidable() { return 1; }

    void FireBullet();
};

