#include "ctDefs.h"
#include "ctLog.h"
#include "ctApp.h"
#include "ctInput.h"
#include "ctTextures.h"
#include "ctAudio.h"
#include "ctRender.h"
#include "ctWindow.h"
#include "ctEntities.h"
#include "ctInputCombo.h"
#include "InputEvent.h"

#include "ctMap.h"

#include "ctFadeToBlack.h"

#include <list>
#include <vector>



ctMap::ctMap() : ctModule()
{
	name = "map";
}

// Destructor
ctMap::~ctMap()
{}

// Called before render is available

bool ctMap::Awake(pugi::xml_node& conf)
{
	
	bool ret = true;

	

	return ret;
}

// Called before the first frame
bool ctMap::Start()
{
	bool ret = true;

	//fx_1 = App->audio->LoadFx("audio/fx/fx_1.wav");
	App->entities->SpawnEntity(0, 0, PLAYER);

	App->entities->SpawnEntity(100, 400, ENEMY);

	App->entities->SpawnEntity(800, 500, ENEMY);

	if(!App->audio->PlayMusic("audio/music/ken.ogg",-1))
		LOG("Error playing music in ctMap Start");


	return ret;
}

// Called each loop iteration
bool ctMap::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool ctMap::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		
		
	}


	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) {
		//Mix_SetPosition(1, sound_angle, sound_distance);
		//Mix_SetDistance(1, fx_distance);
		if (sound_angle <= 20)
			sound_angle = 255;
		else
			sound_angle = 0;
		LOG("ANGLE:%i", sound_angle);
	}
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		//Play3DSound("audio/fx/fx_1.wav");
		App->audio->PauseMusic();
	}
	if (App->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {
		if (sound_distance <= 20)
			sound_distance = 225;
		else
			sound_distance = 1;
		
	}



	//if (!Mix_SetPanning(2, left_ear, right_ear))
		//LOG("Mix_SetPanning: %s\n", Mix_GetError());
	//Mix_SetPanning(0, left_ear, right_ear);
	//Mix_SetPanning(1, left_ear, right_ear);

	

	//if (!Mix_SetPosition(2, 135, 100)) 
	//	printf("Mix_SetPosition: %s\n", Mix_GetError());


	return true;
}

// Called each loop iteration
bool ctMap::PostUpdate()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool ctMap::CleanUp()
{
	

	return true;
}

bool ctMap::Load(pugi::xml_node& load)
{
	bool ret = true;

	return ret;
}

bool ctMap::Save(pugi::xml_node& save) const
{
	bool ret = true;

	return ret;
}

void ctMap::OnUITrigger(UIElement* elementTriggered, UI_State ui_state)
{
}


void ctMap::LoadRect(pugi::xml_node rect_node, SDL_Rect* rect)
{
	rect->x = rect_node.attribute("x").as_float();
	rect->y = rect_node.attribute("y").as_float();
	rect->w = rect_node.attribute("width").as_float();
	rect->h = rect_node.attribute("height").as_float();
}


void ctMap::Play3DSound(const char* id) {

	Mix_Chunk* chunk = Mix_LoadWAV(id);
	Mix_SetPosition(2, sound_angle, sound_distance);
	Mix_PlayChannel(-1, chunk, 0);

}