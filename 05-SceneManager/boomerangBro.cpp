#include "boomerangBro.h"
#include "EatEnemy.h"
#include "PlayScene.h"
#include "Mario.h"

CboomerangBro::CboomerangBro(float x, float y) : CGameObject(x, y)
{
    this->Dir = 1;
    this->ax = 0;
    this->ay = BMRBRO_GRAVITY;
    die_start = -1;
    Friend_killed = false;
    SetState(BMRBRO_STATE_WALKING_LEFT);
}

void CboomerangBro::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    if (state == BMRBRO_STATE_WALKING_LEFT)
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



    if (x1 < this->x) {
        Dir = 1;
        this->vx = BMRBRO_WALKING_SPEED;
        if (abs(this->x - x1) > 6 * 16)
            this->vx = -BMRBRO_WALKING_SPEED;
    }
    else {
        Dir = 0;
        this->vx = -BMRBRO_WALKING_SPEED;
        if (abs(this->x - x1) > 6 * 16)
            this->vx = BMRBRO_WALKING_SPEED;
    }
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
    int aniId = ID_ANI_BMRBRO_WALKING_LEFT;
    if (Dir == 0)
        aniId = ID_ANI_BMRBRO_WALKING_RIGHT;
    CAnimations::GetInstance()->Get(aniId)->Render(x, y);
    RenderBoundingBox();
}

void CboomerangBro::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case BMRBRO_STATE_WALKING_LEFT:
        vx = -BMRBRO_WALKING_SPEED;
        break;
    }
}
