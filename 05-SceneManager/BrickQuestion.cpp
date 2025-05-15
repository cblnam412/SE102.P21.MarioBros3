#include "BrickQuestion.h"
#include "PlayScene.h"
#include "Mushroom.h"
#include "Coin.h"
#include "Leaf.h"

void CBrickQuestion::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (nObj > 0)
		animations->Get(ID_ANI_BRICKQUESTION)->Render(x, y);
	else animations->Get(ID_ANI_EMPTY_BRICKQUESTION)->Render(x, y);
	//RenderBoundingBox();
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
	CCoin* coin = new CCoin(x, y - 16);
	scene->AddObject(coin);
}

void CBrickQuestion::sLeaf() {
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CLeaf *leaf = new CLeaf(x, y - 16);
	scene->AddObject(leaf);
}