#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <fmod.hpp>
#include <string>
#include "SoundStruct.h"

#define SOUNDS 1
#define SPEAKERS 2

class SoundManager
{
private:
	FMOD::System *system = nullptr;
	SoundStruct* listener = nullptr;
	SoundStruct* speakers[SOUNDS]{ nullptr };
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
