#include "objKoopasReturn.h"
#include "Koopas.h"

COKR::COKR(float x, float y) : CGameObject(x, y)
{
    this->ax = 0;
    this->ay = GOOMBA_GRAVITY;
}

void COKR::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - KOOPAS_BBOX_WIDTH / 2;
    top = y - KOOPAS_BBOX_HEIGHT / 2;
    right = left + KOOPAS_BBOX_WIDTH;
    bottom = top + KOOPAS_BBOX_HEIGHT;
}

void COKR::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
};

void COKR::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (!e->obj->IsBlocking()) return;
    if (dynamic_cast<COKR*>(e->obj)) return;

    if (e->ny != 0)
    {
        vy = 0;
    }
}

void COKR::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    vy += ay * dt;
    vx += ax * dt;

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}


void COKR::Render()
{
    //RenderBoundingBox();
}
