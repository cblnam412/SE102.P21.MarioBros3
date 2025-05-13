#include "Platform.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"
#include "Game.h"

void CPlatform::RenderBoundingBox()
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

void CPlatform::Render()
{
	if (this->lengthWidth <= 0 || this->lengthHeight <= 0) return;
	float xx = x; 
	float yy = y;
	CSprites * s = CSprites::GetInstance();

	s->Get(this->sprites[0])->Draw(xx, y);

	if (lengthWidth > 1.0f)
		s->Get(this->sprites[1])->Draw(xx + (lengthWidth - 1) * cellWidth, yy);
	if (lengthHeight > 1.0f)
		s->Get(this->sprites[2])->Draw(xx, yy + (lengthHeight - 1) * cellHeight);
	if (lengthHeight > 1 && lengthWidth > 1)
		s->Get(this->sprites[3])->Draw(xx + (lengthWidth - 1) * cellWidth, yy + (lengthHeight - 1) * cellHeight);

	for (float i = xx + cellWidth; i < xx + (lengthWidth - 1) * cellWidth; i += cellWidth) {
		s->Get(this->sprites[4])->Draw(i, yy);
		if (this->lengthHeight > 1)
			s->Get(this->sprites[5])->Draw(i, yy + (lengthHeight - 1) * cellHeight);
	}

	for (float i = yy + cellHeight; i < yy + (lengthHeight - 1) * cellHeight; i += cellHeight) {
		s->Get(this->sprites[6])->Draw(xx, i);
		if (this->lengthWidth > 1)
			s->Get(this->sprites[7])->Draw(xx + (lengthWidth - 1) * cellWidth, i);
	}

	for (float i = xx + cellWidth; i < xx + (lengthWidth - 1) * cellWidth; i += cellWidth)
		for (float j = yy + cellHeight; j < yy + (lengthHeight - 1) * cellHeight; j += cellHeight)
			s->Get(this->sprites[8])->Draw(i, j);

	RenderBoundingBox();
}

void CPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	float cellWidth_div_2 = this->cellWidth / 2;
	l = x - cellWidth_div_2;
	t = y - this->cellHeight / 2;
	r = l + this->cellWidth * this->lengthWidth;
	b = t + this->cellHeight * this->lengthHeight;
}

int CPlatform::IsDirectionColliable(float nx, float ny)
{
	if (type == 0) {
		return 0;
	}
	if (ny < 0.0f) {
			return 1;
	}
	if (ny < 0.1f && type == 2) {
		return 1;
	}
	return 0;
}