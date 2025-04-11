#include "Leaf.h"

CLeaf::CLeaf()
{
    vx = 0;
    vy = -LEAF_SPEED_Y; // Bay lên ban đầu
    ay = 0.0005f;       // Trọng lực nhẹ để nó rơi từ từ xuống
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    vy += ay * dt;

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLeaf::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
}

void CLeaf::Render()
{
    CAnimations::GetInstance()->Get(ID_ANI_LEAF)->Render(x, y);
    // RenderBoundingBox();
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - LEAF_BBOX_WIDTH / 2;
    t = y - LEAF_BBOX_HEIGHT / 2;
    r = l + LEAF_BBOX_WIDTH;
    b = t + LEAF_BBOX_HEIGHT;
}
