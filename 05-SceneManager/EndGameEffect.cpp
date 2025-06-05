#include "EndGameEffect.h"
#include "Animations.h"
#include "debug.h"

void CEndGameEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (GetTickCount64() - startTime >= SHOW_DURATION)
    {
        isShown = true;
    }
}

void CEndGameEffect::Render()
{
    CAnimations* animations = CAnimations::GetInstance();

    
    animations->Get(ID_ANI_TEXT_COURSE_CLEAR)->Render(x, y);

   
    animations->Get(ID_ANI_TEXT_YOU_GOT_A_CARD)->Render(x, y + 20);

    
    switch (cardType)
    {
    case GOALCARD_MUSHROOM:
        animations->Get(ID_ANI_TEXT_REWARD_MUSHROOM)->Render(x + 70, y + 20);
        break;
    case GOALCARD_PLANT:
        animations->Get(ID_ANI_TEXT_REWARD_FLOWER)->Render(x + 70, y + 20);
        break;
    case GOALCARD_STAR:
        animations->Get(ID_ANI_TEXT_REWARD_STAR)->Render(x + 70, y + 20);
        break;
    }
}
