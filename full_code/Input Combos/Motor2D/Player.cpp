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

	player = { 50,50,50,50 };
	
	
}

Player::~Player()
{
	LOG("Freeing the player");

}

// Called each loop iteration
void Player::Update(float dt)
{
	//DRAW RECT
	SDL_SetRenderDrawColor(App->render->renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(App->render->renderer, &player);
	SDL_RenderPresent(App->render->renderer);


	if (App->input->GetKey(SDL_SCANCODE_DOWN)==KEY_REPEAT && player.y<700)
		player.y+=10;
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && player.y>0)
		player.y -= 10;
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && player.x<970)
		player.x += 10;
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && player.x>0)
		player.x -= 10;

	
}

