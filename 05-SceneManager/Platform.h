#pragma once

#include "GameObject.h"
#include <vector>
// 
// The most popular type of object in Mario! 
// 
class CPlatform : public CGameObject
{
protected:
	int lengthWidth;
	int lengthHeight;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	vector < int > sprites;

public:
	CPlatform(float x, float y,
		float cell_width, float cell_height, int lengthWidth, int lengthHeight,
		vector < int > sprites) :CGameObject(x, y)
	{
		this->lengthWidth = lengthWidth;
		this->lengthHeight = lengthHeight;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->sprites.clear();
		this->sprites = sprites;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();

	int IsDirectionColliable(float nx, float ny);
	int IsBlocking() override { return 1; }
};

typedef CPlatform* LPPLATFORM;