#include "ctDefs.h"
#include "ctLog.h"
#include "ctApp.h"
#include "ctInput.h"
#include "ctTextures.h"
#include "ctAudio.h"
#include "ctRender.h"
#include "ctWindow.h"
#include "ctEntities.h"

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

	
	
	App->entities->SpawnEntity(0, 0, PLAYER);

	player = App->entities->GetPlayer();

	App->entities->SpawnEntity(100, 400, ENEMY);

	App->entities->SpawnEntity(800, 500, ENEMY);

	//TODO 1.2 Add music to the playlist Check "audio/music/----.ogg" for music files. 
	//Short1.ogg, Short2.ogg and Short3.ogg are short songs that will let you see quickly your results

	/*App->audio->AddMusicToList("audio/music/Short1.ogg");
	App->audio->AddMusicToList("audio/music/Short2.ogg");
	App->audio->AddMusicToList("audio/music/Short3.ogg");*/

	//TODO 1.4 Call PlayMusicPlaylist to start a song

	//App->audio->PlayMusicPlaylist();


	//TODO 3.7 Adjust calls to have a playlist type
	App->audio->AddMusicToList("audio/music/Short1.ogg", CASUAL);
	App->audio->AddMusicToList("audio/music/TES V Skyrim Soundtrack - Awake.ogg", CASUAL);

	App->audio->AddMusicToList("audio/music/TES V Skyrim Soundtrack - Combat 1.ogg", BATTLE);
	App->audio->AddMusicToList("audio/music/Short2.ogg", BATTLE);


	App->audio->PlayMusicPlaylist(CASUAL);



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
	App->render->DrawQuad({ 600,400,800,400 }, 40, 240, 220, 240, true, false);

	


	
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		App->audio->PauseMusic();
	}

	//TODO 3.8 Uncomment this!
	if (player->position.x >= 600 && player->position.y >= 400 && App->audio->currentPlaylist==CASUAL)
	{
		LOG("Player in the battle zone");
		App->audio->PlayMusicPlaylist(BATTLE);

	}

	if ((player->position.x < 590 || player->position.y < 390) && App->audio->currentPlaylist == BATTLE)
	{
		LOG("Player in the safe zone");
		App->audio->PlayMusicPlaylist(CASUAL);

	}



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


