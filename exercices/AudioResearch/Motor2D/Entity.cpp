#include "ctApp.h"
#include "Entity.h"
#include "ctRender.h"

Entity::Entity(int x, int y, EntityType type) : position(x, y), type(type)
{
}

Entity::~Entity()
{
}

void Entity::Draw()
{
	switch (type) {
	case PLAYER:
		SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 205, 255);
		SDL_RenderFillRect(App->render->renderer, &rect);
		
		break;
	case ENEMY:
		SDL_SetRenderDrawColor(App->render->renderer, 200, 30, 0, 255);
		SDL_RenderFillRect(App->render->renderer, &rect);
		break;
	default:
		break;
	}

	
}