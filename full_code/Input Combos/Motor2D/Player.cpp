#include "ctDefs.h"
#include "ctLog.h"
#include "ctApp.h"
#include "ctInput.h"
#include "ctRender.h"
#include "ctTextures.h"
#include "ctFadeToBlack.h"
#include "ctAudio.h"
//#include "ctParticles.h"
#include "ctEntities.h"
#include "ctTimer.h"

#include "Combo.h"

#include "Player.h"


Player::Player(int x, int y, EntityType type) : Entity(x, y, type) {

	bool ret = true;

	

}

Player::~Player()
{
	LOG("Freeing the player");

}

// Called each loop iteration
void Player::Update(float dt)
{
	
	
}

