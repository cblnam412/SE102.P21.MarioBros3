#pragma once
#include "GameObject.h"

#define SHOW_DURATION 3000 
#define ID_ANI_TEXT_COURSE_CLEAR    190804
#define ID_ANI_TEXT_YOU_GOT_A_CARD  190805
#define ID_ANI_TEXT_REWARD_MUSHROOM 190806
#define ID_ANI_TEXT_REWARD_FLOWER   190807
#define ID_ANI_TEXT_REWARD_STAR     190808

#define GOALCARD_MUSHROOM  0
#define GOALCARD_PLANT     1
#define GOALCARD_STAR      2

class CEndGameEffect : public CGameObject
{
    ULONGLONG startTime;
    int cardType;
    bool isShown;

public:
    CEndGameEffect(float x, float y, int cardType)
    {
        this->x = x;
        this->y = y;
        this->cardType = cardType;
        this->startTime = GetTickCount64();
        this->isShown = false;
    }

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
    void Render() override;
    void GetBoundingBox(float& l, float& t, float& r, float& b) override {}

    bool IsShown() const { return isShown; }
};
