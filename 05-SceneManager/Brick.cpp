#include "Brick.h"
#include "Animations.h"
#include "Game.h"
#include "Coin.h"
#include "PlayScene.h"

CBrick::CBrick(float x, float y, bool hasSwitch) : CGameObject(x, y)
{
    this->hasSwitch = hasSwitch;
}

void CBrick::Render()
{
    CAnimations* animations = CAnimations::GetInstance();

    if (isSwitchVisible)
    {
        if (isSwitchPressed)
            animations->Get(ID_ANI_SWITCH_HIT)->Render(x, y);
        else
            animations->Get(ID_ANI_SWITCH)->Render(x, y);
    }
    else
    {
        animations->Get(ID_ANI_BRICK)->Render(x, y);
    }

    //RenderBoundingBox();
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (isSwitchVisible && isSwitchPressed)
    {
        this->Delete();
    }
}

void CBrick::SetState(int state)
{
    this->state = state;

    if (state == BRICK_STATE_HITTED && hasSwitch)
        isSwitchVisible = true;

    CGameObject::SetState(state);
}

void CBrick::SetHitted()
{
    if (!isHitted && hasSwitch)
    {
        isHitted = true;
        isSwitchVisible = true;
        SetState(BRICK_STATE_HITTED);
    }
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - BRICK_BBOX_WIDTH / 2;
    t = y - BRICK_BBOX_HEIGHT / 2;
    r = l + BRICK_BBOX_WIDTH;
    b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::SpawnCoin()
{
    CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
    CCoin* coin = new CCoin(x, y - 18); 
    scene->AddObject(coin);
    
}