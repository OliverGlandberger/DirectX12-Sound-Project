#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <fmod.hpp>
#include <string>
#include "SoundStruct.h"

#define EVENTS 2
#define SPEAKERS 3

class SoundManager
{
private:
	FMOD::System *system = nullptr;
	SoundStruct* listener = nullptr;
	SoundStruct* speakers[SPEAKERS]{ nullptr };
	SoundStruct* events[EVENTS];
	SoundStruct* ambience = nullptr;

	void initializeSpeakers();
	void initializeSystem();

	void playAllSounds();
	void playAmbience();

public:
	SoundManager();
	~SoundManager();

	void panRight();
	void panLeft();

	void update();
};

#endif
