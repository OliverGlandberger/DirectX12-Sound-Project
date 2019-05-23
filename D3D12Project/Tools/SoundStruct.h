#pragma once

#include <fmod.hpp>
#include <string>
#include <fmod_common.h>

void ValidityCheck(FMOD_RESULT result);

class SoundStruct {
private:


public:
	// Constructors
	SoundStruct(bool listener);
	SoundStruct(
		std::string fileName,
		FMOD::Sound *sound,
		FMOD::Channel *channel,
		FMOD_VECTOR pos,
		FMOD_VECTOR velocity,
		FMOD_VECTOR forward,
		FMOD_VECTOR up
	);
	~SoundStruct();

	// Variables
	std::string fileName = "";
	FMOD::Sound *sound = nullptr;
	FMOD::Channel *channel = nullptr;
	FMOD_VECTOR Pos{ 0 };
	FMOD_VECTOR Velocity{ 0 };
	FMOD_VECTOR Forward{ 0 };
	FMOD_VECTOR Up{ 0 };

	void play(FMOD::System *system);
	void calculateStereoPan();

};


