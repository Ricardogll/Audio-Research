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
	

	//TODO 6 Uncomment this
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && position.x<200) {
		//TODO 6.1 Use the player and enemy position to get the correct angle and distance in order to call PlayFxOnChannel with fx_1
		App->audio->PlayFxOnChannel(fx_1, App->audio->GetAngle(App->entities->GetPlayer()->position, this->position), App->audio->GetVolumeFromDistance(App->entities->GetPlayer()->position, this->position));

	}



	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && position.x>200) {
		//TODO 6.2 Use the player and enemy position to get the correct angle and distance in order to call PlayFxOnChannel with fx_2
		App->audio->PlayFxOnChannel(fx_2, App->audio->GetAngle(App->entities->GetPlayer()->position, this->position), App->audio->GetVolumeFromDistance(App->entities->GetPlayer()->position, this->position));

	}


}

