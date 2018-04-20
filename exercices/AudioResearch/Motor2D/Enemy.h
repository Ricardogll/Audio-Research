#ifndef __j1Enemy_H__
#define __j1Enemy_H__


#include "ctPoint.h"
#include "Entity.h"

class Enemy : public Entity
{


public:


	//SDL_Rect enemy_rect = { 0,0,0,0 };
	uint fx_1 = 0u;
	uint fx_2 = 0u;
private:




private:


public:

	Enemy(int x, int y, EntityType type);
	~Enemy();

	void Update(float dt);

};

#endif