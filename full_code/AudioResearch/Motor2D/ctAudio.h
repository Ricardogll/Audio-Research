#ifndef __ctAUDIO_H__
#define __ctAUDIO_H__

#include "ctModule.h"
#include "ctPoint.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include <list>

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define MAX_FX 200
#define MAX_DISTANCE 500		 //Set it to the furthest you will be able to hear fx's
#define VOLUME_AT_MAX_DIST 250   //Change as you like. Goes between 255 (volume 0) and 0 (maximum volume)
#define NO_SOUND_DISTANCE 520	 //No sound will be heard from this distance on
#define RADS_TO_DEG 180 / 3.14

struct _Mix_Music;
struct Mix_Chunk;

//TODO 3.1 Add enum to differentiate between CASUAL and BATTLE music
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

	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;

	// Called before quitting
	bool CleanUp();


	//MUSIC
	// Play a music file
	bool PlayMusic(const char* path, int loops=-1, float fade_time = DEFAULT_MUSIC_FADE_TIME);
	bool StopMusic();
	void PauseMusic(); 

	//TODO 3.3 Add a PlaylistType (or however you called your enum) variable to the functions
	bool AddMusicToList(const char* path, PlaylistType pl_type);
	bool PlayMusicPlaylist(PlaylistType pl_type);



	//FX
	// Load a WAV in memory
	unsigned int LoadFx(const char* path);
	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);
	bool PlayFxOnChannel(uint fx, uint channel, uint distance = 1, int repeat = 0);
	// UnLoad WAV
	bool UnLoadFx(uint id);

	uint GetAngle(iPoint pos_player, iPoint pos_enemy);
	uint GetVolumeFromDistance(iPoint pos_player, iPoint pos_enemy);
	void SetChannelsAngles();

private:

	_Mix_Music*			music = nullptr;
	Mix_Chunk*			fx[MAX_FX];

	uint				last_fx = 1;
	uint volume = 50;

	//TODO 3.2 Make 2 lists, one for casual music and other for battle
	std::list<Mix_Music*> playlist_casual;
	std::list<Mix_Music*> playlist_battle;

	//std::list<Mix_Music*> playlist;
	
public:
	

	//TODO 3.2 add a Playlist Type variable to know what playlist we are currently playing
	enum PlaylistType currentPlaylist = NONE;
	
};


#endif // __ctAUDIO_H__