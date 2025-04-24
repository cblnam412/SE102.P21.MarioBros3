#include "ParaGoomba.h"

CParaGoomba::CParaGoomba(float x, float y) : CGoomba(x, y)
{
    this->ax = 0;
    this->ay = PARAGOOMBA_GRAVITY;
    fly_start = -1;
    highest_y = y;
    SetState(PARAGOOMBA_STATE_WALKING);
}

void CParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    {
        left = x - PARAGOOMBA_BBOX_WIDTH / 2;
        top = y - PARAGOOMBA_BBOX_HEIGHT / 2;
        right = left + PARAGOOMBA_BBOX_WIDTH;
        bottom = top + PARAGOOMBA_BBOX_HEIGHT;
    }
}

void CParaGoomba::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
}

void CParaGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (!e->obj->IsBlocking()) return;
    if (dynamic_cast<CParaGoomba*>(e->obj)) return;

    if (e->ny != 0)
    {
        vy = 0;
        if (e->ny < 0 && state == PARAGOOMBA_STATE_WALKING)
        {
            if (GetTickCount64() - fly_start > PARAGOOMBA_FLY_INTERVAL)
            {
                SetState(PARAGOOMBA_STATE_FLYING);
                fly_start = GetTickCount64();
            }
        }
    }
    else if (e->nx != 0)
    {
        vx = -vx;
    }
}

void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (state == PARAGOOMBA_STATE_FLYING)
    {
        ULONGLONG time_since_fly = GetTickCount64() - fly_start;
        float progress = min(time_since_fly / (float)PARAGOOMBA_FLY_INTERVAL, 1.0f);

        if (progress < 0.4f) 
        {
            float jump_progress = progress / 0.4f;
            float target_y = highest_y - PARAGOOMBA_FLY_HEIGHT * jump_progress;
            vy = (target_y - y) * 0.2f; 
        }
        else if (progress < 0.6f) 
        {
            float target_y = highest_y - PARAGOOMBA_FLY_HEIGHT;
            vy = (target_y - y) * 0.1f;
        }
        else 
        {
            
            float fall_progress = (progress - 0.6f) / 0.4f;
            float target_y = highest_y - PARAGOOMBA_FLY_HEIGHT * (1.0f - fall_progress);
            vy = (target_y - y) * 0.2f; 
            if (progress >= 1.0f)
            {
                SetState(PARAGOOMBA_STATE_WALKING);
                fly_start = GetTickCount64();
            }
        }
    }

    vy += ay * dt;
    vx += ax * dt;

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CParaGoomba::Render()
{
    int aniId = ID_ANI_PARAGOOMBA_WALKING;

    if (state == PARAGOOMBA_STATE_FLYING)
    {
        aniId = ID_ANI_PARAGOOMBA_FLYING;
    }

    CAnimations::GetInstance()->Get(aniId)->Render(x, y);
    RenderBoundingBox();
}

void CParaGoomba::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case PARAGOOMBA_STATE_WALKING:
        vx = -PARAGOOMBA_WALKING_SPEED;
        ay = PARAGOOMBA_GRAVITY;
        break;

    case PARAGOOMBA_STATE_FLYING:
        vx = -PARAGOOMBA_WALKING_SPEED;
        ay = 0; 
        highest_y = y; 
        break;
    }
}