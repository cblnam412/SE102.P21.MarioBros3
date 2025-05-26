#pragma once
#include "GameObject.h"

class Teleport : public CGameObject
{
	float tlx, tly;
public:
	Teleport(float x, float y , float tlx , float tly) : CGameObject(x, y) {
		this->tlx = tlx;
		this->tly = tly;
	};

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	virtual void Render() {
		//RenderBoundingBox();
	};

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt) {};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) {};

	float getTLX() {
		return this->tlx;
	}
	float getTLY() {
		return this->tly;
	}
};
