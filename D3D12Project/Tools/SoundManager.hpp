#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include "../include/FMOD Studio API Windows/api/lowlevel/inc/fmod.hpp"

class SoundManager
{
private:
	FMOD::System *system = nullptr;
	FMOD::Sound *sounds[4];

public:
	SoundManager();
	~SoundManager();

	void update();
};

#endif
