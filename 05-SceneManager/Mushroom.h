#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.05f

#define ID_ANI_MUSHROOM 12000
#define ID_ANI_GREEN_MUSHROOM 12002

#define	MUSHROOM_WIDTH 16
#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16


class CMushroom : public CGameObject {
protected:
	float ax;
	float ay;
    bool isGreen;
public:
	CMushroom(float x, float y) : CGameObject(x, y) {
		this->ay = MUSHROOM_GRAVITY;
		this->ax = 0;
        this->isGreen = false;
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
};