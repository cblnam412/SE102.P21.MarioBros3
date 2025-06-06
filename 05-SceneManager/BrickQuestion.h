#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICKQUESTION 18500
#define ID_ANI_BRICKQUESTIONBRICK   18502
#define ID_ANI_EMPTY_BRICKQUESTION 18501
#define BRICKQUESTION_WIDTH 16
#define BRICKQUESTION_BBOX_WIDTH 16
#define BRICKQUESTION_BBOX_HEIGHT 16

#define JUMP_DURATION   100

class CBrickQuestion : public CGameObject {
protected:
	int type;
	int nObj;
    int typebrick;

    bool isJumping = false;
    bool koopasOn = false;
    float oldY;
    ULONGLONG jumpStartTime = 0;
public:
	CBrickQuestion(float x, float y, int type, int nObj, int typebrick) : CGameObject(x, y) {
		this->type = type;
		this->nObj = nObj;
        this->typebrick = typebrick;
        this->oldY = y;
	}


	void Render();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

    void startJump();

	int getType() {
		return this->type;
	}

	int getnOBbj() {
		return this->nObj;
	}

	void decnObj() {
		this->nObj--;
	}

    bool getJumping() {
        return isJumping;
    }

    void setKoopasOn(bool ok) {
        this->koopasOn = ok;
    }

	void sMushroom();
	void sCoin();
	void sLeaf();
    void sGreenMushroom();
};