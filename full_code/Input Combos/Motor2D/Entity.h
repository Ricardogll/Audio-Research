#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "ctPoint.h"
#include "ctEntities.h"

struct SDL_Texture;

class Entity
{
protected:
	
	bool key_entities_speed = false;

public:
	iPoint position = iPoint(0, 0);
	EntityType type = EntityType::NO_TYPE;
	bool to_destroy = false;

public:
	Entity(int x, int y, EntityType type);
	virtual ~Entity();

	virtual void Update(float dt) {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void SetEntitiesSpeed(float dt) {};

};

#endif // __ENTITY_H__