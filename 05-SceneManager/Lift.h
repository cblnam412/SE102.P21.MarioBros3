#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_SPRITES_LIFT	1001000

#define LIFT_BBOX_WIDTH 48
#define LIFT_BBOX_HEIGHT 16

#define LIFT_SPEED 0.02f
#define LIFT_SPEED_DROP	0.02f

class CLift : public CGameObject {
protected:
    float prevX, prevY;
    bool isDropping;
public:
	CLift(float x, float y) : CGameObject(x, y) {
		this->vx = -LIFT_SPEED;
        isDropping = false;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsDirectionColliable(float nx, float ny);
	int IsBlocking() override { return 1; }

    void swapVXY();

    bool IsDropping() const { return isDropping; }

    void GetDisplacement(float& dx, float& dy) {
        dx = x - prevX;
        dy = y - prevY;
    }

    float GetVy() const { return vy; }

};