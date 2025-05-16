#pragma once
#include "GameObject.h"

class EatEnemy : public CGameObject
{
public:
	EatEnemy(float x, float y) : CGameObject(x, y) {};

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	virtual void Render() {
		RenderBoundingBox();
	};

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt) {};
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};
