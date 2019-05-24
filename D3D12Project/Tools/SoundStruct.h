#pragma once

#include <fmod.hpp>
#include <string>
#include <fmod_common.h>

void ValidityCheck(FMOD_RESULT result);

class SoundStruct {
private:
	float abs(FMOD_VECTOR vector);

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
	float baseVolume = 1.0f;	// Fmod default value
	float distanceFactor = 25.0f;

	// Play the audio with a specific starting volume if we want | Deletes volume for you!
	void play(FMOD::System *system, float *volume = nullptr);
	void updateVolume(FMOD_VECTOR listenerPos);
	void calculateStereoPan();	// Not really implemented


};


