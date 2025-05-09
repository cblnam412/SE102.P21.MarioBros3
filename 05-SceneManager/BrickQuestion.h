#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICKQUESTION 18500
#define BRICKQUESTION_WIDTH 16
#define BRICKQUESTION_BBOX_WIDTH 16
#define BRICKQUESTION_BBOX_HEIGHT 16

class CBrickQuestion : public CGameObject {
public:
	CBrickQuestion(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};