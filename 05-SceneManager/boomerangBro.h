#pragma once
#include "GameObject.h"

#define BMRBRO_GRAVITY 0.002f
#define BMRBRO_WALKING_SPEED 0.02f


#define BMRBRO_BBOX_WIDTH 16
#define BMRBRO_BBOX_HEIGHT 24
#define BMRBRO_BBOX_HEIGHT_DIE 7

#define BMRBRO_DIE_TIMEOUT 500

#define BMRBRO_STATE_WALKING_LEFT 100
#define BMRBRO_STATE_WALKING_RIGHT  200
#define BMRBRO_STATE_DIE 200

#define ID_ANI_BMRBRO_WALKING_LEFT 13100
#define ID_ANI_BMRBRO_WALKING_RIGHT 13101

class CboomerangBro : public CGameObject
{
protected:
    float ax;
    float ay;
    int Dir;
    bool Friend_killed;

    ULONGLONG die_start;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

    virtual int IsCollidable() {
        if (Friend_killed)
            return 0;
        return 1;
    };
    virtual int IsBlocking() { return 0; }
    virtual void OnNoCollision(DWORD dt);

    virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
    CboomerangBro(float x, float y);
    virtual void SetState(int state);
    float GetX() { return x; }
    float GetY() { return y; }
    void setFriendKilled(bool Friend_killed) {
        this->Friend_killed = Friend_killed;
    }
    void Move();
};