#include "ctApp.h"
#include "Entity.h"
#include "ctRender.h"

Entity::Entity(int x, int y, EntityType type) : position(x, y), type(type)
{
}

Entity::~Entity()
{
}

void Entity::Draw(SDL_Texture* sprites)
{
	
	

}