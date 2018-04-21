
I am [Ricardo Gutiérrez](https://www.linkedin.com/in/ricardo-guti%C3%A9rrez-5a7a0b161/?trk=onboarding-landing&dl=no), student of the [Bachelor’s Degree in Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/). This content is generated for the second year’s subject Project 2, under supervision of lecturer [Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).

# Introduction

In this guide I'll walk you through 2 different audio related problems we might need to take the audio on our game to the next step. Firstly we'll talk about a general music manager and some of the features in it. Later on, we'll see spacial audio, were we'll be able to hear audio coming from 360 angles.

# Music Manager

Firstly I'd like to recommend having the SDL_mixer [wiki](http://sdl.beuc.net/sdl.wiki/SDL_mixer) ready to look up any useful function we might use. Let's start by taking a look at the audio module *ctAudio*.
For this part we'll mostly use and create functions under the MUSIC label. 

## Basic Music Functions

![Basic Music Functions](https://github.com/Ricardogll/Audio-Research/blob/master/docs/MusicFuncs.png)

* **PlayMusic:** This will allow us to start playing music giving the path to the file, the amount of times we want it to loop (-1 for infinite) and a fade in and fade out time in case we are already playing a song.

* **StopMusic:** Here we'll just halt and free the music.

* **PauseMusic:** On the other hand, with this we'll be able to pause and unpause as we like. 

## Time to make a playlist!

Now this is were the real thing starts. We want to have a playlist of music that can loop over and over through the songs we add. Since we need [Mix_Music](http://sdl.beuc.net/sdl.wiki/Mix_Music) to load and play music, lets have a list of Mix_Music* that will allow us to push and pop either back or front as we need. 

### TODO

Now add the music of the path recieved to your playlist. Once done, you can start to add songs to the playlist on the scene, in my case *ctMap*.

*img de los pasos

Now we'll need to play the music in our playlist. Take a look at PlayMusic function to have an idea on how we can start playing music. Don't forget to add LOG's using [Mix_GetError()](http://sdl.beuc.net/sdl.wiki/Mix_GetError) in case anything fails and we need to know what happened.

*img pasos

Explicar funcion al principio del cpp para q llame cuando acabe la cancion

luego cuando explique cambio de musica hacer todos de poner enum, nueva lista, etc. Since we are later making the music swap between casual music and battle music I'll add an extra list to differentiate between these two.
