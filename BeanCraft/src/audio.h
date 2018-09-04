#pragma once
#include "SDL.h"

class Audio {
public:
	~Audio();
	void load(const char* filename);
	void play();

private:
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 *wavBuffer;
	SDL_AudioDeviceID deviceID;
};