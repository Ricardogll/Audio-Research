#ifndef __j1Player_H__
#define __j1Player_H__


#include "ctPoint.h"
#include "Entity.h"

class Player : public Entity
{


public:


	//SDL_Rect player_rect = { 0,0,0,0 };
	

private:


	

private:


public:

	Player(int x, int y, EntityType type);
	~Player();

	void Update(float dt);
	
};

#endif