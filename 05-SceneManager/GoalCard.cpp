#include "GoalCard.h"
#include "Animations.h"
#include "Game.h"
#include "debug.h"

void CGoalCard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (!isCollected) 
    {
        if (GetTickCount64() - start_change > TIME_CHANGE_GOALCARD)
        {
            if (card == GOALCARD_MUSHROOM) card = GOALCARD_PLANT;
            else if (card == GOALCARD_PLANT) card = GOALCARD_STAR;
            else if (card == GOALCARD_STAR) card = GOALCARD_MUSHROOM;
            start_change = GetTickCount64();
        }

    }
    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGoalCard::Render()
{

    int aniId = ID_ANI_GOALCARD_MUSHROOM;
    CAnimations* animations = CAnimations::GetInstance();
    if (card == GOALCARD_MUSHROOM) aniId = ID_ANI_GOALCARD_MUSHROOM;
    else if (card == GOALCARD_PLANT) aniId = ID_ANI_GOALCARD_PLANT;
    else if (card == GOALCARD_STAR) aniId = ID_ANI_GOALCARD_STAR;
    animations->Get(aniId)->Render(x, y);
    //RenderBoundingBox();
}


void CGoalCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - CARD_BBOX_WIDTH / 2;
    t = y - CARD_BBOX_HEIGHT / 2;
    r = l + CARD_BBOX_WIDTH;
    b = t + CARD_BBOX_HEIGHT;
}

void CGoalCard::SetState(int state) {
    switch (state) {
    case CARD_STATE_COLLECTED:
        isCollected = true;
        vy = -SPEED_GOALCARD;
        break;
    }
    CGameObject::SetState(state);
}