#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <fmod.hpp>
#include <string>
//#include "../../include/D3D/"

#define SOUNDS 3

struct SoundStruct {
	std::string fileName = "";
	FMOD::Sound *sound = nullptr;
	FMOD::Channel *channel = nullptr;
	FMOD_VECTOR Pos{ 0 };
	FMOD_VECTOR Velocity{ 0 };
	FMOD_VECTOR Forward{ 0 };
	FMOD_VECTOR Up{ 0 };
};

class SoundManager
{
private:
	FMOD::System *system = nullptr;
	SoundStruct* listener;
	SoundStruct* speakers[SOUNDS];

public:
	SoundManager();
	~SoundManager();



	void update();
};

#endif
