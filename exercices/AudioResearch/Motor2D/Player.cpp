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
#include "Player.h"


Player::Player(int x, int y, EntityType type) : Entity(x, y, type) {

	bool ret = true;

	rect = { x,y,50,50 };
	
	
}

Player::~Player()
{
	LOG("Freeing the player");

}

// Called each loop iteration
void Player::Update(float dt)
{
	

	//MOVE
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && rect.y < 700) {
		rect.y += 10;
		App->render->camera.y += 10;
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && rect.y > 0) {
		rect.y -= 10;
		App->render->camera.y -= 10;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && rect.x < 970) {
		rect.x += 10;
		App->render->camera.x += 10;
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && rect.x > 0) {
		rect.x -= 10;
		App->render->camera.x -= 10;
	}

	
	position.x = rect.x;
	position.y = rect.y;
}

