#include "EatEnemy.h"

#include "Sprite.h"
#include "Sprites.h"
#include "Platform.h"
#include "Goomba.h"

#include "Textures.h"
#include "Game.h"

void EatEnemy::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth / 2 + rect.right / 2;
	float yy = y - this->cellHeight / 2 + rect.bottom / 2;

	CGame::GetInstance()->Draw(xx - cx, yy - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void EatEnemy::Render()
{
	RenderBoundingBox();
}

void EatEnemy::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * this->lengthWidth;
	b = t + this->cellHeight * this->lengthHeight;
}

void EatEnemy::OnCollisionWith(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
}
