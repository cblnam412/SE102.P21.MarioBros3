#include "Paragoomba.h"

CParagoomba::CParagoomba(float x, float y) : CGameObject(x, y)
{
    this->ax = 0;
    this->ay = PARAGOOMBA_GRAVITY;
    fly_start = -1;
    jump_count = 0;
    SetState(PARAGOOMBA_STATE_WALKING);
}

void CParagoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - PARAGOOMBA_BBOX_WIDTH / 2;
    right = left + PARAGOOMBA_BBOX_WIDTH;

    if (state == PARAGOOMBA_STATE_FLY)
    {
        top = y - PARAGOOMBA_BBOX_HEIGHT_FLY / 2;
        bottom = top + PARAGOOMBA_BBOX_HEIGHT_FLY;
    }
    else
    {
        top = y - PARAGOOMBA_BBOX_HEIGHT / 2;
        bottom = top + PARAGOOMBA_BBOX_HEIGHT;
    }
}

void CParagoomba::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
}

void CParagoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (!e->obj->IsBlocking()) return;
    if (dynamic_cast<CParagoomba*>(e->obj)) return;

    if (e->ny != 0)
    {
        vy = 0;

        // Nếu tiếp đất thì thực hiện nhảy
        if (state == PARAGOOMBA_STATE_WALKING)
        {
            if (jump_count < PARAGOOMBA_JUMP_COUNT)
            {
                vy = PARAGOOMBA_JUMP_VY;
                jump_count++;
            }
            else
            {
                vy = PARAGOOMBA_HIGH_JUMP_VY;
                jump_count = 0;
                vx = -vx; // Quay đầu
            }
        }
    }
    else if (e->nx != 0)
    {
        vx = -vx;
    }
}

void CParagoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    vy += ay * dt;
    vx += ax * dt;

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CParagoomba::Render()
{
    int aniId = ID_ANI_PARAGOOMBA_WALKING;
    if (state == PARAGOOMBA_STATE_FLY)
    {
        aniId = ID_ANI_PARAGOOMBA_FLY;
    }
    CAnimations::GetInstance()->Get(aniId)->Render(x, y);
    RenderBoundingBox();
}

void CParagoomba::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case PARAGOOMBA_STATE_FLY:
        fly_start = GetTickCount64();
        y += (PARAGOOMBA_BBOX_HEIGHT - PARAGOOMBA_BBOX_HEIGHT_FLY) / 2;
        vx = 0;
        vy = 0;
        ay = 0;
        break;
    case PARAGOOMBA_STATE_WALKING:
        vx = -PARAGOOMBA_WALKING_SPEED;
        ay = PARAGOOMBA_GRAVITY;
        break;
    }
}
