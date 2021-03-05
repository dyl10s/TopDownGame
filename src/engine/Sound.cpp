#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "engine/Sound.hpp"

Sound::Sound() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

Sound::~Sound() {
    Mix_CloseAudio();
}

void Sound::playBGMusic(const char* filename) {
    Mix_Music* backgroundSound = Mix_LoadMUS(filename);
	if( backgroundSound == NULL )
    {
        printf( "Failed to load background music: %s\n", Mix_GetError() );
    }
    Mix_PlayMusic(backgroundSound, -1);
}

void Sound::setVolume(int volume) {
    Mix_VolumeMusic(volume);
}

// void Sound::playSoundEffect(const char* filename) {
//     Mix_LoadWAV* soundEffect = Mix_LoadWAV(filename);
//     if( soundEffect == NULL )
//     {
//         printf( "Failed to load sound effect: %s\n", Mix_GetError() );
//     }
// }
