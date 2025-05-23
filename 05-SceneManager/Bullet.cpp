#include "Bullet.h"
#include "Animations.h"
#include "debug.h"




void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
    x += vx * dt;
    y += vy * dt;
    DebugOut(L"[BULLET] Update: x=%.2f, y=%.2f, vx=%.2f, vy=%.2f\n", x, y, vx, vy);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBullet::OnNoCollision(DWORD dt) {
    x += vx * dt;
    y += vy * dt;
}

void CBullet::OnCollisionWith(LPCOLLISIONEVENT e) {

    
    this->Delete();
}

void CBullet::Render() {
    CAnimations::GetInstance()->Get(ID_ANI_BULLET)->Render(x, y);
    RenderBoundingBox();
}

void CBullet::GetBoundingBox(float& l, float& t, float& r, float& b) {
    l = x - PLANT_BULLET_BBOX_WIDTH / 2;
    t = y - PLANT_BULLET_BBOX_HEIGHT / 2;
    r = l + PLANT_BULLET_BBOX_WIDTH;
    b = t + PLANT_BULLET_BBOX_HEIGHT;
}
