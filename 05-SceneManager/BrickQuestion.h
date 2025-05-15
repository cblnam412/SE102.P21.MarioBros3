#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICKQUESTION 18500
#define ID_ANI_EMPTY_BRICKQUESTION 18501
#define BRICKQUESTION_WIDTH 16
#define BRICKQUESTION_BBOX_WIDTH 16
#define BRICKQUESTION_BBOX_HEIGHT 16

class CBrickQuestion : public CGameObject {
protected:
	int type;
	int nObj;
public:
	CBrickQuestion(float x, float y, int type, int nObj) : CGameObject(x, y) {
		this->type = type;
		this->nObj = nObj;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int getType() {
		return this->type;
	}

	int getnOBbj() {
		return this->nObj;
	}

	void decnObj() {
		this->nObj--;
	}

	void sMushroom();
	void sCoin();
	void sLeaf();
};