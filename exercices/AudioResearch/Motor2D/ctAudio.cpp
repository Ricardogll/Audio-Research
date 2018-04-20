#include "ctDefs.h"
#include "ctLog.h"
#include "ctAudio.h"

#include "ctInput.h"
#include "ctApp.h"
#include <math.h>

#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

//bool song_finished = false; //BORRAR
//void SongFinished() {
//	song_finished = true;
//
//}

ctAudio::ctAudio() : ctModule()
{
	music = NULL;
	name = "audio";
	//currentPlaylist = CASUAL;//BORRAR
}

// Destructor
ctAudio::~ctAudio()
{}

bool ctAudio::Load(pugi::xml_node& save) {
	bool ret = true;

	Mix_VolumeMusic(save.child("volume").attribute("music").as_int(volume));

	return ret;
}

bool ctAudio::Save(pugi::xml_node& save)const {
	bool ret = true;

	if (save.child("volume").empty()) {
		save = save.append_child("volume");
		save.append_attribute("music").set_value(Mix_VolumeMusic(-1));
	}
	else {
		save.child("volume").attribute("music").set_value(Mix_VolumeMusic(-1));
	}

	return ret;
}

// Called before render is available
bool ctAudio::Awake(pugi::xml_node& config)
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		active = false;
		ret = true;
	}

	// load support for the JPG and PNG image formats
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		active = false;
		ret = true;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		active = false;
		ret = true;
	}

	//Mix_AllocateChannels(360); //BORRAR
	SetChannelsAngles();
	Mix_VolumeMusic(volume);


	//Mix_HookMusicFinished(SongFinished);//BORRAR

	return ret;
}

bool ctAudio::Update(float dt)
{
	if (!active)
		return true;

	if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN) {
		Mix_VolumeMusic(Mix_VolumeMusic(-1) + 10);
		Mix_Volume(-1, Mix_Volume(-1, -1) + 10);
		volume=Mix_VolumeMusic(-1);
	}

	if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN) {
		if (Mix_VolumeMusic(-1) < 10)
			Mix_VolumeMusic(0);
		else
			Mix_VolumeMusic(Mix_VolumeMusic(-1) - 10);

		if (Mix_Volume(-1, -1) < 10)
			Mix_Volume(-1, 0);
		else
			Mix_Volume(-1, Mix_Volume(-1, -1) - 10);
		volume = Mix_VolumeMusic(-1);
	}
	

	/*if (song_finished) {//BORRAR
		
		song_finished = false;

		Mix_Music* temp;

		switch (currentPlaylist) {
		case CASUAL:
			temp = playlist_casual.front();
			playlist_casual.pop_front();
			playlist_casual.push_back(temp);
			break;
		case BATTLE:
			temp = playlist_battle.front();
			playlist_battle.pop_front();
			playlist_battle.push_back(temp);
			break;
		default:
			break;
			
		}
		temp = NULL;
		PlayMusicPlaylist(currentPlaylist);
	}*/

	return true;
}

// Called before quitting
bool ctAudio::CleanUp()
{
	if (!active)
		return true;

	LOG("Freeing music, closing Mixer and Audio subsystem");

	if (music != NULL)
	{
		Mix_FreeMusic(music);
	}
	//playlist_casual.clear(); //BORRAR
	//playlist_battle.clear();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	return true;
}

// Play a music file
bool ctAudio::PlayMusic(const char* path, int loops, float fade_time)
{
	bool ret = true;

	if (!active)
		return false;

	if (music != NULL)
	{
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic(int(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if (music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if (fade_time > 0.0f)
		{
			if (Mix_FadeInMusic(music, loops, (int)(fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if (Mix_PlayMusic(music, loops) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

bool ctAudio::StopMusic() {
	Mix_FreeMusic(music);
	music = nullptr;
	Mix_HaltMusic();
	return true;
}

// Load WAV
unsigned int ctAudio::LoadFx(const char* path)
{
	if (!active)
		return 0;

	uint ret = 0;
	Mix_Chunk* chunk = Mix_LoadWAV(path);
	
	if (chunk == nullptr)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx[last_fx] = chunk;
		ret = last_fx++;
		if (last_fx == MAX_FX) {
			last_fx = 0;
			ret = last_fx;
		}
	}

	return ret;
}

// Play WAV
bool ctAudio::PlayFx(unsigned int id, int repeat)
{

	if (!active)
		return false;

	bool ret = false;

	if (fx[id] != nullptr)
	{
		Mix_PlayChannel(-1, fx[id], repeat);
		ret = true;
	}

	return ret;
}
//bool ctAudio::PlayFxOnChannel(uint id, uint channel, uint distance, int repeat)//BORRAR
//{
//
//	if (!active)
//		return false;
//
//	bool ret = false;
//
//	
//
//	if (fx[id] != nullptr)
//	{
//
//		while (Mix_Playing(channel) == 1) {//if channel is playing look for next one
//			channel++;
//			if (channel >= 360)
//				channel = 0;
//		}
//
//		Mix_SetPosition(channel, channel, distance);
//		Mix_PlayChannel(channel, fx[id], repeat);
//		ret = true;
//	}
//	return ret;
//}

// UnLoad WAV
bool ctAudio::UnLoadFx(uint id)
{
	if (!active)
		return true;

	bool ret = false;

	if (fx[id] != nullptr)
	{
		Mix_FreeChunk(fx[id]);
		fx[id] = nullptr;
		ret = true;
		//last_fx--;
	}

	return ret;
}

//uint ctAudio::GetAngle(iPoint pos_player, iPoint pos_enemy) { //BORRAR?
//
//	//We make player the center of a new frame. So its position on this frame will be (0,0), and calculate the new enemy position accordint to this frame.
//	iPoint vec_p = { 0,1 };//We want to get the angle that is created with the Y axis, so we will caculate the angle between axis y (0,1) and 
//	iPoint vec_e=pos_enemy-pos_player;// this new vector of enemy-player positions.
//
//	double dot = (vec_p.x*vec_e.x) + (vec_p.y*vec_e.y);  //Dot product
//	double det = (vec_p.x*vec_e.y) - (vec_p.y*vec_e.x);//Determinant
//	
//	float ret_f = (atan2(det, dot)) * RADS_TO_DEG;
//	ret_f += 180;
//	uint ret = static_cast<uint>(ret_f);
//	return ret;
//}


//uint ctAudio::GetVolumeFromDistance(iPoint pos_player, iPoint pos_enemy) { //BORRAR?
//	uint ret = 0;
//	double dist_in_pixels= sqrt(abs(pow((pos_enemy.x - pos_player.x), 2) + pow((pos_enemy.y - pos_player.y), 2)));
//
//	if (dist_in_pixels >= NO_SOUND_DISTANCE) {
//		return 255;
//	}
//
//	double dist_change_scale = (255.0 / MAX_DISTANCE) * dist_in_pixels;  //Set scale as you like changing MAX_DISTANCE
//
//	ret = static_cast<uint>(dist_change_scale);
//	
//	if (ret > 255) 
//		ret = VOLUME_AT_MAX_DIST;
//	
//	
//
//	return ret;
//}


void ctAudio::PauseMusic()
{
	if (active)
	{
		// If music is playing, handle the pause request
		if (Mix_PlayingMusic() == 1)
		{
			if (Mix_PausedMusic() == 1)
			{
				// If we receive a pause request and the music is already paused, resume it.
				Mix_ResumeMusic();
			}
			else
			{
				// Otherwise, pause the music
				Mix_PauseMusic();
			}
		}
	}
}

//Set every channel to have the same angle as the channel number
//void ctAudio::SetChannelsAngles()  //BORRAR
//{
//
//	uint angle = 0;
//
//	
//	for (int i = 0; i <= 360; i++) {
//		Mix_SetPosition(i, i, 1);
//	}
//
//}

//bool ctAudio::AddMusicToList(const char* path, PlaylistType pl_type) {  //BORRAR
//	
//	Mix_Music* song = Mix_LoadMUS(path);
//
//	if (!song) {
//		LOG("Cannot add music %s to playlist. Mix_GetError(): %s", path, Mix_GetError());
//		return false;
//	}
//
//	switch (pl_type) {
//	case CASUAL:
//		playlist_casual.push_back(song);
//		break;
//	case BATTLE:
//		playlist_battle.push_back(song);
//		break;
//	default:
//
//		break;
//	}
//
//	song = NULL;
//	return true;
//}



//bool ctAudio::PlayMusicPlaylist(PlaylistType pl_type, float fade_time) { //BORRAR
//
//	bool ret = true;
//
//	if (!active)
//		return false;
//
//
//
//	switch (pl_type) {
//	case CASUAL:
//		
//		music = playlist_casual.front();
//		currentPlaylist = CASUAL;
//		if (Mix_PlayMusic(music, 1) == -1) {
//			LOG("Cannot play music. Mix_GetError(): %s", Mix_GetError());
//			return false;
//		}
//		
//		break;
//	case BATTLE:
//		
//		music = playlist_battle.front();
//		currentPlaylist = BATTLE;
//		if (Mix_PlayMusic(music, 1) == -1) {
//			LOG("Cannot play music. Mix_GetError(): %s", Mix_GetError());
//			return false;
//		}
//		break;
//	default:
//		break;
//
//	}
//	
//	return ret;
//}




