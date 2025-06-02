#include "boomerangBro.h"
#include "EatEnemy.h"
#include "PlayScene.h"
#include "Mario.h"

CboomerangBro::CboomerangBro(float x, float y) : CGameObject(x, y)
{
    this->ax = 0;
    this->ay = BMRBRO_GRAVITY;
    die_start = -1;
    Friend_killed = false;
    SetState(BMRBRO_STATE_WALKING);
}

void CboomerangBro::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    if (state == BMRBRO_STATE_DIE)
    {
        left = x - BMRBRO_BBOX_WIDTH / 2;
        top = y - BMRBRO_BBOX_HEIGHT_DIE / 2;
        right = left + BMRBRO_BBOX_WIDTH;
        bottom = top + BMRBRO_BBOX_HEIGHT_DIE;
    }
    else if (state == BMRBRO_STATE_WALKING)
    {
        left = x - BMRBRO_BBOX_WIDTH / 2;
        top = y - BMRBRO_BBOX_HEIGHT / 2;
        right = left + BMRBRO_BBOX_WIDTH;
        bottom = top + BMRBRO_BBOX_HEIGHT;
    }
}

void CboomerangBro::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
};

void CboomerangBro::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (dynamic_cast<EatEnemy*>(e->obj)) {
        this->Delete();
        return;
    }

    if (!e->obj->IsBlocking()) return;
    if (dynamic_cast<CboomerangBro*>(e->obj)) return;

    if (e->ny != 0)
    {
        vy = 0;
    }
    else if (e->nx != 0)
    {
        vx = -vx;
    }
}

void CboomerangBro::Move() {
    CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
    CMario* mario = (CMario*)scene->GetPlayer();

    float x1, y1;
    mario->GetPosition(x1 , y1);

    if (x1 < this->x)
        this->vx = BMRBRO_WALKING_SPEED;
    else this->vx = -BMRBRO_WALKING_SPEED;
}

void CboomerangBro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    Move();
    vy += ay * dt;
    vx += ax * dt;

    if ((state == BMRBRO_STATE_DIE) && (GetTickCount64() - die_start > BMRBRO_DIE_TIMEOUT))
    {
        isDeleted = true;
        return;
    }


    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CboomerangBro::Render()
{
    //CAnimations::GetInstance()->Get(aniId)->Render(x, y);
    RenderBoundingBox();
}

void CboomerangBro::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case BMRBRO_STATE_DIE:
        die_start = GetTickCount64();
        y += (BMRBRO_BBOX_HEIGHT - BMRBRO_BBOX_HEIGHT_DIE) / 2;
        vx = 0;
        vy = 0;
        ay = 0;
        break;
    case BMRBRO_STATE_WALKING:
        vx = -BMRBRO_WALKING_SPEED;
        break;
    }
}
