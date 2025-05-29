#pragma once
#include "GameObject.h"
#include "objKoopasReturn.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.03f
#define KOOPAS_ROTATE_SPEED 0.15f
#define KOOPAS_JUMP_SPEED 0.1f    
#define KOOPAS_FLY_SPEED   0.1f   

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 28
#define SHELL_BBOX_HEIGHT 16

#define KOOPAS_SHELL_TIMEOUT 4500

#define KOOPAS_STATE_WALKING_LEFT 0
#define KOOPAS_STATE_WALKING_RIGHT 1
#define KOOPAS_STATE_SHELL 2
#define KOOPAS_STATE_RELIVE 3
#define KOOPAS_STATE_ROTATE 4

#define ID_ANI_RED_WALKING_LEFT 7000
#define ID_ANI_RED_WALKING_RIGHT 7001
#define ID_ANI_RED_SHELL 7002
#define ID_ANI_RED_RELIVE 7003
#define ID_ANI_RED_ROTATE 7004

#define ID_ANI_GREEN_WALKING_LEFT	7100
#define ID_ANI_GREEN_WALKING_RIGHT	7101
#define ID_ANI_GREEN_SHELL	7102
#define ID_ANI_GREEN_RELIVE	7103
#define ID_ANI_GREEN_ROTATE	7104

#define ID_ANI_GREEN_FLYING_LEFT	7200
#define ID_ANI_GREEN_FLYING_RIGHT	7201

#define ID_ANI_RED_FLYING_LEFT  7210

class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;
	int type;
	ULONGLONG shell_start;

    float startY;
    int   dirY;

	bool killFriend;

    COKR* okr;

	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e) {};
	void OnCollisionWithPlant(LPCOLLISIONEVENT e) {};
    void OnCollisionWithBrickQuestion(LPCOLLISIONEVENT e);

public:
	CKoopas(float x, float y, int type);

	void setVX(float vx);
	void setXY(float x, float y) {
		this->x = x;
		this->y = y;
	}
	void setAY(float ay) {
		this->ay = ay;
	}

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void SetState(int state);

    void updateRedParaKoopas(DWORD dt);

	bool checkReturn(LPCOLLISIONEVENT e);

	int getAni() {
		return	7000 + type + state;
	}
	
	int getType() {
		return type;
	}

    void setType(int type) {
        this->type = type;
    }
};
