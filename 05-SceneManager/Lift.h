#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_SPRITES_LIFT	1001000

#define LIFT_BBOX_WIDTH 48
#define LIFT_BBOX_HEIGHT 16

#define LIFT_SPEED 0.03f
#define LIFT_SPEED_DROP	0.05f

class CLift : public CGameObject {
protected:
public:
	CLift(float x, float y) : CGameObject(x, y) {
		this->vx = -LIFT_SPEED;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsDirectionColliable(float nx, float ny);
	int IsBlocking() override { return 1; }

	void swapVXY(){
		vx = 0;
		vy = LIFT_SPEED_DROP;
	}
};