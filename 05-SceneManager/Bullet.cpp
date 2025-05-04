#include "Bullet.h"
#include "Animations.h"

CBullet::CBullet(float x, float y, float vx, float vy) : CGameObject(x, y) {
	this->vx = vx;
	this->vy = vy;
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	x += vx * dt;
	y += vy * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBullet::Render() {
	CAnimations::GetInstance()->Get(ID_ANI_BULLET)->Render(x, y);
	RenderBoundingBox();
}

void CBullet::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x - PLANT_BULLET_BBOX_WIDTH / 2;
	t = y - PLANT_BULLET_BBOX_HEIGHT / 2;
	r = l + PLANT_BULLET_BBOX_WIDTH;
	b = t + PLANT_BULLET_BBOX_HEIGHT;
}
