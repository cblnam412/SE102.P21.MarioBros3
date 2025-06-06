#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.05f

#define ID_ANI_MUSHROOM 12000
#define ID_ANI_GREEN_MUSHROOM 12002
#define ID_ANI_TEX_1UP  12003

#define	MUSHROOM_WIDTH 16
#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16

#define TIME_1UP_DISPLAY 800

class CMushroom : public CGameObject {
protected:
    float ax;
    float ay;
    bool isGreen;
    bool isEaten;
    bool show1UpText;
    ULONGLONG show1UpStartTime;
    float effectX, effectY;

public:
    CMushroom(float x, float y) : CGameObject(x, y) {
        this->ay = MUSHROOM_GRAVITY;
        this->ax = 0;
        this->isGreen = false;
        this->show1UpText = false;
        this->show1UpStartTime = 0;
        this->isEaten = false;
    }
    void Render();
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    virtual int IsCollidable() { return 1; };
    void OnCollisionWith(LPCOLLISIONEVENT e);
    int IsBlocking() { return 0; }
    virtual void OnNoCollision(DWORD dt);
    void SetGreen(bool green) {
        this->isGreen = green;
    }
    bool IsGreen() { return isGreen; }
    void Trigger1Up();
    void SetEaten(bool eaten) { this->isEaten = eaten; }
};