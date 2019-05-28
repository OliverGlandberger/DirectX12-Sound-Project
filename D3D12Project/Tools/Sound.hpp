#ifndef SOUND_HPP
#define SOUND_HPP

#define SOUND_COUNT 3

#include <DirectXMath.h>
#include "Fmod/fmod.h"
#include "Fmod/fmod.hpp"

class Sound
{
private:
	FMOD_RESULT result;
	FMOD::System* soundSystem = nullptr;
	FMOD::Channel* ambianceChan = nullptr;
	FMOD::Channel* soundChan[SOUND_COUNT] = { nullptr };

	FMOD::Sound* ambiance = nullptr;
	FMOD::Sound* sounds[SOUND_COUNT] = { nullptr };

	FMOD_VECTOR soundPos[SOUND_COUNT];
	FMOD_VECTOR cameraPosNew;
	FMOD_VECTOR soundDistance;

	float tempVectorDistance;

	void checkResult(FMOD_RESULT _result);

	float calcVectorDist(FMOD_VECTOR _vector);
	
public:
	Sound();
	~Sound();

	void playAllSounds();

	void update();
};

#endif
