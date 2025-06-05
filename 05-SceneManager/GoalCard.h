#pragma once
#include "GameObject.h"
#include "Animations.h"

#define CARD_BBOX_HEIGHT 16
#define CARD_BBOX_WIDTH 16

#define SPEED_GOALCARD 0.08f
#define TIME_CHANGE_GOALCARD 150

#define GOALCARD_MUSHROOM  0
#define GOALCARD_STAR      1
#define GOALCARD_PLANT     2


#define ID_ANI_GOALCARD_MUSHROOM    190801
#define ID_ANI_GOALCARD_PLANT   190802
#define ID_ANI_GOALCARD_STAR    190803
#define CARD_STATE_COLLECTED 100

class CGoalCard : public CGameObject
{
    int card;
    bool isCollected;
    bool isEaten;
    ULONGLONG start_change;
   
public:
    CGoalCard(float x, float y) : CGameObject(x, y) {
        card = GOALCARD_MUSHROOM;
        isCollected = false;
        isEaten = false;
        start_change = GetTickCount64();
    }
    void Render();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void OnNoCollision(DWORD dt) {
        x += vx * dt;
        y += vy * dt;
    }
    virtual int IsCollidable() { return 1; }
    virtual int IsBlocking() { return 1; }
    void GetBoundingBox(float& l, float& t, float& r, float& b);


    int GetCard() { return card; }
    void SetCard(int card) { this->card = card; }
    bool GetCollected() { return isCollected; }
    void SetState(int state);
};
