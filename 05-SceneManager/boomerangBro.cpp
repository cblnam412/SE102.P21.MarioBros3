#include "boomerangBro.h"
#include "EatEnemy.h"
#include "PlayScene.h"
#include "Mario.h"
#include "boomerang.h"

CboomerangBro::CboomerangBro(float x, float y) : CGameObject(x, y)
{
    this->Dir = 1;
    this->ax = 0;
    this->ay = BMRBRO_GRAVITY;
    die_start = -1;
    
    this->isJumping = false;
    this->isThrowing = false;
    this->throw_start = 0;
    this->jump_start = 0;
    last_throw_time = 0;
    throwCount = 0;

    SetState(BMRBRO_STATE_WALKING_LEFT);
}

void CboomerangBro::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
     left = x - BMRBRO_BBOX_WIDTH / 2;
     top = y - BMRBRO_BBOX_HEIGHT / 2;
     right = left + BMRBRO_BBOX_WIDTH;
     bottom = top + BMRBRO_BBOX_HEIGHT;
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

    float distance = abs(x1 - this->x);
    ULONGLONG current_time = GetTickCount64();
    if (!isJumping && !isThrowing &&
        distance <= 6 * 16 &&
        distance >= 4 * 16 &&
        (current_time - last_throw_time > BMRBRO_THROW_COOLDOWN))
    {
        SetState(BMRBRO_STATE_JUMP);
        return;
    }

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
    if (!isJumping && !isThrowing) {
        Move();
    }

    vy += ay * dt;
    vx += ax * dt;

    if (isJumping && (GetTickCount64() - jump_start > BMRBRO_JUMP_TIMEOUT)) {
        SetState(BMRBRO_STATE_THROW);
    }

    if (isThrowing && (GetTickCount64() - throw_start > BMRBRO_THROW_TIMEOUT)) {
        isThrowing = false;
        throwCount++;
        last_throw_time = GetTickCount64();

        CBoomerang* boomerang = new CBoomerang(x, y, Dir);
        CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
        scene->AddObject(boomerang);
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
        vy = 0;
        break;
    case BMRBRO_STATE_JUMP:
        vy = -BMRBRO_JUMP_SPEED;
        isJumping = true;
        jump_start = GetTickCount64();
        break;

    case BMRBRO_STATE_THROW:
        vx = 0; 
        vy = 0; 
        isJumping = false;
        isThrowing = true;
        throw_start = GetTickCount64();
        break;
    }
}
