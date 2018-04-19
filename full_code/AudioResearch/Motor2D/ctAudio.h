#ifndef __ctAUDIO_H__
#define __ctAUDIO_H__

#include "ctModule.h"
#include "ctPoint.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include <list>

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_FX 200
#define MAX_DISTANCE 500		 //Set it to the furthest you will be able to hear fx's
#define VOLUME_AT_MAX_DIST 250   //Change as you like. Goes between 255 (volume 0) to 0 (maximum volume)
#define RADS_TO_DEG 180 / 3.14
struct _Mix_Music;
struct Mix_Chunk;

enum PlaylistType
{
	CASUAL = 0,
	BATTLE,


	NONE=-1,
};


class ctAudio : public ctModule
{
public:

	ctAudio();

	// Destructor
	virtual ~ctAudio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called each loop iteration
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, int loops=-1, float fade_time = DEFAULT_MUSIC_FADE_TIME);
	bool StopMusic();
	void PauseMusic();
	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);
	bool PlayFxOnChannel(uint fx, uint channel,  uint distance=1, int repeat = 0);
	// UnLoad WAV
	bool UnLoadFx(uint id);

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	uint GetAngle(iPoint pos_player, iPoint pos_enemy);
	uint GetDistance(iPoint pos_player, iPoint pos_enemy);
	void SetChannelsAngles();
	
	bool AddMusicToList(const char* path, PlaylistType pl_type);
	bool PlayMusicPlaylist(PlaylistType pl_type);

private:

	

	_Mix_Music*			music = nullptr;
	Mix_Chunk*			fx[MAX_FX];

	uint				last_fx = 1;
	std::list<Mix_Music*> playlist_casual;
	std::list<Mix_Music*> playlist_battle;
	

public:

	enum PlaylistType currentPlaylist = NONE;
};


#endif // __ctAUDIO_H__