#pragma once

#include "GameObject.h"
#include <vector>
// 
// The most popular type of object in Mario! 
// 
class EatEnemy : public CGameObject
{
protected:
	int lengthWidth;
	int lengthHeight;				// Unit: cell 
	float cellWidth;
	float cellHeight;

public:
	EatEnemy(float x, float y,
		float cell_width, float cell_height, int lengthWidth, int lengthHeight) :CGameObject(x, y)
	{
		this->lengthWidth = lengthWidth;
		this->lengthHeight = lengthHeight;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};
