#include "Mushroom.h"
#include "PlayScene.h"
#include "Game.h"
#include "Mario.h"

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects){

        vy += ay * dt;
        vx += ax * dt;
    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
};

void CMushroom::Render()
{

	CAnimations* animations = CAnimations::GetInstance();
    if (isGreen)
        animations->Get(ID_ANI_GREEN_MUSHROOM)->Render(x, y);
    else
	animations->Get(ID_ANI_MUSHROOM)->Render(x, y);

	//RenderBoundingBox();
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{

    if (!e->obj->IsBlocking()) return;
    if (dynamic_cast<CMushroom*>(e->obj)) return;

    if (e->ny < 0) 
    {
        if (vx == 0) {
            vx = -MUSHROOM_WALKING_SPEED;
        }
        vy = 0;
    }
    else if (e->nx != 0) 
    {
        vx = -vx; 
    }
}


void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSHROOM_BBOX_WIDTH / 2;
	t = y - MUSHROOM_BBOX_HEIGHT / 2;
	r = l + MUSHROOM_BBOX_WIDTH;
	b = t + MUSHROOM_BBOX_HEIGHT;
}
