#pragma once

#include <SDL_mixer.h>

typedef struct {
    Mix_Chunk* chunk;
} Audio;

void initAudio(Audio* audio, const char* filename) {
    char path[256];
    snprintf(path, sizeof(path), "audio/%s.wav", filename);
    audio->chunk = Mix_LoadWAV(path);
}

void playAudio(Audio* audio) {
    if (audio->chunk) {
        Mix_PlayChannel(-1, audio->chunk, 0);
    }
}

void freeAudio(Audio* audio) {
    if (audio->chunk) {
        Mix_FreeChunk(audio->chunk);
        audio->chunk = NULL;
    }
}
