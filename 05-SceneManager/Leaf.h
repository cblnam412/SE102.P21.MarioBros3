#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_LEAF 13000

#define	LEAF_WIDTH 16
#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 16
#define LEAF_GRAVITY 0.5f;

class CLeaf : public CGameObject {
protected:
	float ay;
public:
	CLeaf(float x, float y) : CGameObject(x, y) { ay = 0.005; vx = 0.05; }
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual int IsCollidable() { return 0; };
};