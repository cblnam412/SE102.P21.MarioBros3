#include "boomerang.h"

CBoomerang::CBoomerang(float x, float y, int dir) : CGameObject(x, y)
{
    this->dir = dir;
    phase = 0;
    phase_start = GetTickCount64();
    vx = (dir == 0) ? BOOMERANG_SPEED_X : -BOOMERANG_SPEED_X;
    vy = -BOOMERANG_SPEED_Y;
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (GetTickCount64() - phase_start > 500 && phase == 0) {
        phase = 1;
        vx = -vx;
        vy = BOOMERANG_SPEED_Y;
    }

    vy += BOOMERANG_GRAVITY * dt;
    x += vx * dt;
    y += vy * dt;
}

void CBoomerang::Render() {
    int aniId = ID_ANI_BOOMERANG;
    CAnimations::GetInstance()->Get(aniId)->Render(x, y);
    RenderBoundingBox();
}

void CBoomerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
     left = x - BMR_BBOX_WIDTH / 2;
     top = y - BMR_BBOX_HEIGHT / 2;
     right = left + BMR_BBOX_WIDTH;
     bottom = top + BMR_BBOX_HEIGHT;
}