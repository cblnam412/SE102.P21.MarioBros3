	#pragma once
	#include "GameObject.h"

	#define PLANT_BULLET_SPEED_X 0.1f
	#define PLANT_BULLET_SPEED_Y 0.05f
	#define PLANT_BULLET_BBOX_WIDTH 8
	#define PLANT_BULLET_BBOX_HEIGHT 8

	#define ID_ANI_BULLET 15000

	class CBullet : public CGameObject {
		float vx, vy;
	public:
		CBullet(float x, float y, float vx, float vy);
		void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		void Render();
		void GetBoundingBox(float& l, float& t, float& r, float& b);

		int IsCollidable() override { return 1; }         
		int IsBlocking() override { return 0; }
	};