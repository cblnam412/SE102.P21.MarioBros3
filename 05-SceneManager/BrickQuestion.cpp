﻿#include "BrickQuestion.h"
#include "PlayScene.h"
#include "Mushroom.h"
#include "Coin.h"
#include "Leaf.h"
#include "Koopas.h"

void CBrickQuestion::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
    if (nObj > 0) {
        if (typebrick == 1)
            animations->Get(ID_ANI_BRICKQUESTION)->Render(x, y);
        else animations->Get(ID_ANI_BRICKQUESTIONBRICK)->Render(x, y);
    }
	else animations->Get(ID_ANI_EMPTY_BRICKQUESTION)->Render(x, y);
	//RenderBoundingBox();
}

void CBrickQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

    if (isJumping)
    {
        ULONGLONG now = GetTickCount64();
        ULONGLONG elap = now - jumpStartTime;

        if (elap < JUMP_DURATION){
            y = oldY - 4.0f;
        }
        else if (elap < JUMP_DURATION * 2){
            y = oldY;
        }
        else{
            isJumping = false;
        }
    }
    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBrickQuestion::startJump()
{
    if (!isJumping) {
        isJumping = true;
        jumpStartTime = GetTickCount64();
    }
}

void CBrickQuestion::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICKQUESTION_BBOX_WIDTH / 2;
	t = y - BRICKQUESTION_BBOX_HEIGHT / 2;
	r = l + BRICKQUESTION_BBOX_WIDTH;
	b = t + BRICKQUESTION_BBOX_HEIGHT;
}

void CBrickQuestion::sMushroom() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CMushroom* mroom = new CMushroom(x, y - 16);
	scene->AddObject(mroom);
}

void CBrickQuestion::sCoin() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CCoin* coin = new CCoin(x, y - 18);
	scene->AddObject(coin);
	coin->setVY(-0.5f);
}

void CBrickQuestion::sLeaf() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CLeaf *leaf = new CLeaf(x, y - 32);
	scene->AddObject(leaf);
}

void CBrickQuestion::sGreenMushroom() {
    CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
    CMushroom* gmroom = new CMushroom(x, y - 16);  
    gmroom->SetGreen(true); 
    scene->AddObject(gmroom);
}