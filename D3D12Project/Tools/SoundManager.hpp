#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <fmod.hpp>
//#include "../../include/D3D/"

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
