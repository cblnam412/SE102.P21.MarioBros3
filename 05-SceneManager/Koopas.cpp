#define _USE_MATH_DEFINES  
#include <cmath>
#include <string>
#include "Koopas.h"
#include "Brick.h"
#include "Goomba.h"
#include <iostream>
#include "EatEnemy.h"
#include "PlayScene.h"
#include "Mario.h"
#include "BrickQuestion.h"
#include "PlantEnemy.h"

CKoopas::CKoopas(float x, float y, int type) : CGameObject(x, y)
{
	this->type = type;
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	shell_start = -1;

    this->startY = y;
    this->dirY = 1;

    if (type == 0 || type == 210) {
        okr = new COKR(x, y);
        CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
        scene->AddObject(okr);
    }
    else okr = nullptr;

	killFriend = false;
	SetState(KOOPAS_STATE_WALKING_LEFT);
}


void CKoopas::setVX(float vx) {
	this->vx = vx;
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_RELIVE || state == KOOPAS_STATE_ROTATE)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - SHELL_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + SHELL_BBOX_HEIGHT;
	}
	else if (state == KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<EatEnemy*>(e->obj)) {
		this->Delete();
		return;
	}
	//if (!e->obj->IsBlocking()) return;

    if (dynamic_cast<CMario*>(e->obj))
        return;

	if (e->obj->IsBlocking())
	{
		if (type == 0 && (state == KOOPAS_STATE_WALKING_LEFT || state == KOOPAS_STATE_WALKING_RIGHT)) {
			if (checkReturn(e)) {
				if (state == KOOPAS_STATE_WALKING_LEFT)
					SetState(KOOPAS_STATE_WALKING_RIGHT);
				else SetState(KOOPAS_STATE_WALKING_LEFT);
			}
		}
		
		if (e->ny != 0 && type != 200)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			if (state == KOOPAS_STATE_WALKING_LEFT)
				SetState(KOOPAS_STATE_WALKING_RIGHT);
			else if (state == KOOPAS_STATE_WALKING_RIGHT)
				SetState(KOOPAS_STATE_WALKING_LEFT);
			else
				vx = -vx;
		}
	}

	if (!killFriend)
		return;
	if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	else if (dynamic_cast<CGoomba*>(e->obj)) {
		OnCollisionWithGoomba(e);
    }
    else if (dynamic_cast<CBrickQuestion*>(e->obj)) {
        OnCollisionWithBrickQuestion(e);
    }
    else if (dynamic_cast<CKoopas*>(e->obj))
        OnCollisionWithKoopas(e);
    else if (dynamic_cast<CPlantEnemy*>(e->obj)) {
        OnCollisionWithPlant(e);
    }
}
void CKoopas::OnCollisionWithPlant(LPCOLLISIONEVENT e) {
    CPlantEnemy* plant = dynamic_cast<CPlantEnemy*>(e->obj);
    plant->Delete();
}
void CKoopas::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
    CKoopas* otherKoopas = dynamic_cast<CKoopas*>(e->obj);

    if (this->killFriend)
    {
        otherKoopas->Delete();
    }
}

void CKoopas::OnCollisionWithBrickQuestion(LPCOLLISIONEVENT e)
{
    if (state != KOOPAS_STATE_ROTATE)
        return;
    CBrickQuestion* brickquestion = dynamic_cast<CBrickQuestion*>(e->obj);
    
    if (brickquestion->getJumping())
        this->Delete();

    brickquestion->decnObj();


    if (brickquestion->getType() == 1)
    {
        CPlayScene* current_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
        CMario* mario = (CMario*)current_scene->GetPlayer();
         if (mario->GetLevel() < MARIO_LEVEL_BIG)
             brickquestion->sMushroom();
         else brickquestion->sLeaf();
    }
    else if (brickquestion->getType() == 0) {
        brickquestion->sCoin();
    }
}

void CKoopas::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	if (state == KOOPAS_STATE_ROTATE)
	{
		if (e->nx != 0)
			e->obj->Delete();
	}
}

void CKoopas::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
    goomba->SetState(GOOMBA_STATE_DIE_2);
    if (state == KOOPAS_STATE_SHELL) {
        CPlayScene* current_scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
        CMario* mario = (CMario*)current_scene->GetPlayer();
        mario->releaseKoopas();
        this->Delete();
    }
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (type == 200) {
		ULONGLONG now = GetTickCount64();
		float time = (now % 2000) / 1000.0f; 
		
		vy = -KOOPAS_JUMP_SPEED * cos(M_PI * time);
    }
    else if (type == 210) {
        updateRedParaKoopas(dt);
    }

	vy += ay * dt;
	vx += ax * dt;


	if (state == KOOPAS_STATE_SHELL)
	{
		DWORD shell_time = GetTickCount64() - shell_start;

		if (shell_time > KOOPAS_SHELL_TIMEOUT)
		{
			DWORD shake_duration = 1500;
			DWORD shake_time = shell_time - KOOPAS_SHELL_TIMEOUT;

			if (shake_time <= shake_duration)
			{
				float frequency = 10.0f;
				float shake_speed = 0.05f;
				vx = shake_speed * sin(2 * M_PI * frequency * shake_time / 1000.0f);
			}
			else
			{
				SetState(KOOPAS_STATE_RELIVE);
			}
		}
	}

	if (state == KOOPAS_STATE_RELIVE)
	{
		DWORD relive_time = GetTickCount64() - shell_start;
		const DWORD shake_duration = 1000;

		if (relive_time <= shake_duration)
		{
			const float frequency = 12.0f;
			const float shake_speed = 0.08f;
			vx = shake_speed * sin(2 * M_PI * frequency * relive_time / 1000.0f);
		}
		else
		{
			y -= (KOOPAS_BBOX_HEIGHT - SHELL_BBOX_HEIGHT) / 2;
			SetState(KOOPAS_STATE_WALKING_LEFT);
		}
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::updateRedParaKoopas(DWORD dt) {
    const float AMPLITUDE = 80.0f;  
    const float SPEED = KOOPAS_FLY_SPEED / 2;
    vy = SPEED * dirY;
    y += vy * dt;
    if (y >= startY + AMPLITUDE) {
        y = startY + AMPLITUDE;
        dirY = -1;   
    }
    else if (y <= startY - AMPLITUDE) {
        y = startY - AMPLITUDE;
        dirY = 1; 
    }
    vx = 0;
}

void CKoopas::Render()
{
	int aniId = getAni();

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case KOOPAS_STATE_SHELL:
		shell_start = GetTickCount64();
		vx = 0;
        killFriend = false;
		break;

	case KOOPAS_STATE_WALKING_LEFT:
		ay = KOOPAS_GRAVITY;
		vx = -KOOPAS_WALKING_SPEED;
		break;

	case KOOPAS_STATE_WALKING_RIGHT:
		ay = KOOPAS_GRAVITY;
		vx = KOOPAS_WALKING_SPEED;
		break;

	case KOOPAS_STATE_RELIVE:
		shell_start = GetTickCount64();
		vx = 0;
		break;

	case KOOPAS_STATE_ROTATE:
		ay = KOOPAS_GRAVITY;
		setVX(-KOOPAS_ROTATE_SPEED);
		killFriend = true;
		break;
	}
}

int Await;

#include <windows.h>
#include <sstream>
void DebugDM(float Await) {
    std::ostringstream oss;
    oss << "Await = " << Await;  
    OutputDebugStringA(oss.str().c_str());  
    OutputDebugStringA("\n");
}


bool CKoopas::checkReturn(LPCOLLISIONEVENT e) {

	float checkX = x - KOOPAS_BBOX_WIDTH / 2 + vx * 0.01f;
    float checkR = checkX + KOOPAS_BBOX_WIDTH;

	float l, t, r, b;
	e->obj->GetBoundingBox(l, t, r, b);

    onBQ = (dynamic_cast<CBrickQuestion*>(e->obj));

    if (l > checkX && state == KOOPAS_STATE_WALKING_LEFT) {
        if (Await <= 0) {
            this->okr->setXY(x - 16 , y);
            Await = 10;
        }
        else {
            Await--;
        }
        float l1, t1, r1, b1;
        this->okr->GetBoundingBox(l1, t1, r1, b1);
        if (y - KOOPAS_BBOX_HEIGHT / 2 < t1) {
            Await = 0;
        }
        return  y - KOOPAS_BBOX_HEIGHT / 2 < t1;
    }
    else if (checkR > r && state == KOOPAS_STATE_WALKING_RIGHT) {
        if (Await <= 0) {
            this->okr->setXY(x + 16, y);
            Await = 10;
        }
        else {
            Await--;
        }
        float l1, t1, r1, b1;
        this->okr->GetBoundingBox(l1, t1, r1, b1);
        if (y - KOOPAS_BBOX_HEIGHT / 2 < t1) {
            Await = 0;
        }
        return y - KOOPAS_BBOX_HEIGHT / 2 < t1;
    }
    
	return false;
}