#include "ctDefs.h"
#include "ctLog.h"
#include "ctApp.h"
#include "ctInput.h"
#include "ctRender.h"
#include "ctTextures.h"
#include "ctFadeToBlack.h"
#include "ctAudio.h"
#include "ctEntities.h"
#include "ctTimer.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(int x, int y, EntityType type) : Entity(x, y, type) {

	bool ret = true;

	rect = { x,y,50,50 };
	fx_1 = App->audio->LoadFx("audio/fx/fx_1.wav");
	fx_2 = App->audio->LoadFx("audio/fx/fx_2.wav");
}

Enemy::~Enemy()
{
	LOG("Freeing the player");
	App->audio->UnLoadFx(fx_1);
	App->audio->UnLoadFx(fx_2);
}

// Called each loop iteration
void Enemy::Update(float dt)
{
	//DRAW RECT
	//SDL_SetRenderDrawColor(App->render->renderer, 255, 0, 0, 255);
	//SDL_RenderFillRect(App->render->renderer, &enemy_rect);
	//SDL_RenderPresent(App->render->renderer);
	

	//MOVE
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && position.x<200) {
		/*Mix_SetPosition(0, App->audio->GetAngle(App->entities->GetPlayer()->position, this->position), App->audio->GetDistance(App->entities->GetPlayer()->position, this->position));
		Mix_SetPosition(1, App->audio->GetAngle(App->entities->GetPlayer()->position, this->position), App->audio->GetDistance(App->entities->GetPlayer()->position, this->position));

		App->audio->PlayFx(fx_1);
		LOG("Player:%i,%i. Enemy:%i,%i. Angle=%i, Dist=%i", App->entities->GetPlayer()->position.x, App->entities->GetPlayer()->position.y, this->position.x, this->position.y,
															App->audio->GetAngle(App->entities->GetPlayer()->position, this->position),
															App->audio->GetDistance(App->entities->GetPlayer()->position, this->position));*/
		App->audio->PlayFxOnChannel(fx_1, App->audio->GetAngle(App->entities->GetPlayer()->position, this->position), App->audio->GetDistance(App->entities->GetPlayer()->position, this->position));

	}



	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && position.x>200) {
	/*	Mix_SetPosition(0, App->audio->GetAngle(App->entities->GetPlayer()->position, this->position), App->audio->GetDistance(App->entities->GetPlayer()->position, this->position));
		Mix_SetPosition(1, App->audio->GetAngle(App->entities->GetPlayer()->position, this->position), App->audio->GetDistance(App->entities->GetPlayer()->position, this->position));

		App->audio->PlayFx(fx_2);
		LOG("Player:%i,%i. Enemy:%i,%i. Angle=%i, Dist=%i", App->entities->GetPlayer()->position.x, App->entities->GetPlayer()->position.y, this->position.x, this->position.y,
			App->audio->GetAngle(App->entities->GetPlayer()->position, this->position),
			App->audio->GetDistance(App->entities->GetPlayer()->position, this->position));
	*/

		App->audio->PlayFxOnChannel(fx_2, App->audio->GetAngle(App->entities->GetPlayer()->position, this->position), App->audio->GetDistance(App->entities->GetPlayer()->position, this->position));

	}



	//position.x = rect.x;
	//position.y = rect.y;
}

