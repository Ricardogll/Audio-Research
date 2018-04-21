
I am [Ricardo Gutiérrez](www.linkedin.com/in/ricardo-gutiérrez-5a7a0b161), student of the [Bachelor’s Degree in Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/). This content is generated for the second year’s subject Project 2, under supervision of lecturer [Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).

# Introduction

In this guide I'll walk you through 2 different audio related problems we might need to take the audio on our game to the next step. Firstly we'll talk about a general music manager and some of the features in it. Later on, we'll see spacial audio, were we'll be able to hear audio coming from 360 angles.

# Music Manager

Firstly I'd like to recommend having the SDL_mixer [wiki](http://sdl.beuc.net/sdl.wiki/SDL_mixer) ready to look up any useful function we might use. Let's start by taking a look at the audio module *ctAudio*.
For this part we'll mostly use and create functions under the MUSIC label. 

## Basic Music Functions

![Basic Music Functions](/docs/MusicFuncs.png?raw=true "Basic Music Functions")


* **PlayMusic:** This will allow us to start playing music giving the path to the file, the amount of times we want it to loop (-1 for infinite) and a fade in and fade out time in case we are already playing a song.

* **StopMusic:** Here we'll just halt and free the music.

* **PauseMusic:** On the other hand, with this we'll be able to pause and unpause as we like. 

## Time to make a playlist!

Now this is were the real thing starts. We want to have a playlist of music that can loop over and over through the songs we add. Since we need [Mix_Music](http://sdl.beuc.net/sdl.wiki/Mix_Music) to load and play music, lets have a list of Mix_Music* that will allow us to push and pop either back or front as we need.

*img std::list playlist 8

### TODO 1

Now go to the function **AddMusicToList** and add the music of the path recieved to your playlist. Once done, you can start to add songs to the playlist on the scene, in my case *ctMap*.

*img de los pasos1 y 3

Now we'll need to play the music in our playlist. Take a look at **PlayMusic** function to have an idea on how we can start playing music. Don't forget to add LOG's using [Mix_GetError()](http://sdl.beuc.net/sdl.wiki/Mix_GetError) in case anything fails and we need to know what happened.

*img pasos2

Now we can start playing our playlist on our scene.

*img map metiendo musica en la pl y playingplaylist 3

### TODO 2

But what happens is that the first song plays and that's all. Now we'll need to somehow know when a song is finished to go onto the next one right? This is where [Mix_HookMusicFinished](https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_69.html) comes. This will allow us to set up a function to be called whenever a song ends.

So for now we only want a basic function SongFinished that will set a bool song_finished to true, then we'll work from there.

TIP:

MixHookMusicFinished asks for a normal function, not a member function and will give you this error if you do this mistake.

*img error de hacer funcion en el ctaudio 4
*Argument of type "void (ctAudio::*)()" is incompatible with paramater of type "void(*)()"

There are 2 ways to avoid this:

* Declare your function and bool as static members. This means that there will only be one instance of this variable shared between all instantiations of our App.

**static** void SongFinished();
**static** bool song_finished();

* Or the simplest solution, making the function and bool normal functions by declaring them outside the audio module.

In my case I'll use the second way.

*imagen func arriba de audio.cpp 5

And dont forget to link the function with MixHookMusicFinished

*imagen start con mixhook 6

Now we will have a bool that will set true every time a song ends. Let's head to our game loop, in my case the Update function. Add a condition that will check if a song has just finished, and if its true cycle the music through the playlist and set our bool back to false so we don't end up coming back into this condition every game loop.

TIP:

Since in previous TODO 1.3 we started the playlist by the front, we will have to pop this and put it back at the end of the list. Don't forget to PlayMusicPlaylist again once you've done that.

*img del if(song_finished) 7

Now we should be able to hear the songs we added to the playlist cycling over and over. *(Use songs: Short1.ogg, Short2.ogg and Short3.ogg for 5 to 10 secongs long songs to check how you did).*

*video cycling through music

## Now lets make 2 playlists for different moods!

Now that we've learned how to make a playlist, we will go into the next step. Make 2 playlists.

We will differentiate this 2 by CASUAL and BATTLE playlists. What we want to accomplish is to have the playlists change whenever we approach certain enemy or zone in our game. In this case we will try to make music be peaceful on the black part of the map and on the cyan part we will enter a combat zone and change playlist.

### TODO 3

We will have to go over the previous TODO's and adjust them for 2 types of playlist.

First we will add an enum that will help us in the following steps.

*foto enum 9

We will also need to have 2 lists of Mix_Music for our playlist.

*foto playlists casual/battle 10

In order to know what playlist we are playing currently lets add a PlaylistType variable. And don't forget to make it start in CASUAL or BATTLE in our constructor.

*foto enum currentPlaylist 10

For the last step on the .h we will have to adjust the parameters we recieve on AddMusicToList and PlayMusicPlaylist.

*foto funciones con PlaylistType pl_type 11

Now lets head into AddMusicToList and change it so we can add a song to one or the other playlist depending on what PlaylistType we recieve.

*foto 12

Next, lets do the same with PlayMusicPlaylist and adjust it so we play a song based on the playlist type we recieve. Remember to set your enum variable to the type of music you are playing!

*foto13

For the final adjustment we will go into the song_finished condition on our Update. Same as before, we will have to cycle ONLY throught the playlist that is currently playing.

*foto14

Then head to the map and make our calls have a playlist type!

Now we have all the necessary. Go to the loop of the map and uncomment a simple condition I made so that the music type changes once we enter the cyan area or we leave it.

*foto15

*video cambiando musica

This is just a way to show you that to change playlist we only need to call PlayMusicPlaylist with the type we want, so feel free to change the condition to "Enemy can see me", "Entering boss room" or whatever you want inside your game!

## What to do now?

Now it's your turn to get creative. 

Do you want to have a different song every time you change zone? 

Do you want to return to the same second of a song you changed after entering combat? [This will help you](https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_65.html)

Remember to always keep the [wiki](http://sdl.beuc.net/sdl.wiki/SDL_mixer) close and everything will be fine!

//*******************


luego cuando explique cambio de musica hacer todos de poner enum, nueva lista, etc. Since we are later making the music swap between casual music and battle music I'll add an extra list to differentiate between these two.
