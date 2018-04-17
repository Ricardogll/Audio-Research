#ifndef __j1Player_H__
#define __j1Player_H__

#include "ctAnimation.h"
#include "ctPoint.h"
#include "Entity.h"

class Player : public Entity
{


public:

	//player's current frame (entity)
	SDL_Rect current_frame = { 0,0,0,0 };

	

private:

	

private:


public:

	Player(int x, int y, EntityType type);
	~Player();

	void Update(float dt);
};

#endif