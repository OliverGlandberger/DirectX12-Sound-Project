#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <fmod.hpp>
#include <string>
#include "SoundStruct.h"

#define EVENTS 2
#define SPEAKERS 1	// These are speakers IN-GAME

// Allocates an array of T with Size where every index is equal to pValue
template<typename T>
T* *initAs(int size, T* pValue);


class SoundManager
{
private:
	FMOD::System *system = nullptr;
	SoundStruct* listener = nullptr;
	SoundStruct* speakers[SPEAKERS]{ nullptr };
	SoundStruct* events[EVENTS];
	SoundStruct* ambience = nullptr;

	int test = 1;

	void initializeSpeakers();
	void initializeSystem();

	// Array needs to be the size of SPEAKERS | Deletes pVolumes[] for you!
	void playAllSounds(float* *pVolumes = nullptr);
	void playAmbience(float* *pVolumes = nullptr);	// Currently specific to '1' ambience

public:
	SoundManager();
	~SoundManager();

	void panRight();
	void panLeft();

	void update();
};

/*


	//float* mixMatrix = new float[SPEAKERS * (SOUNDS +1)]{
	//	0, 0,
	//	0, 0
	//};

	//int* speakers0 = new int();
	//int* sounds0 = new int();
	//*speakers0 = SPEAKERS;
	//*sounds0 = SOUNDS;

	//speakers[0]->channel->getMixMatrix(mixMatrix, speakers0, sounds0);
	//FMOD_RESULT res = speakers[0]->channel->setPan(-1.0f);
	//speakers[0]->channel->getMixMatrix(mixMatrix, speakers0, sounds0);
//	ValidityCheck(speakers[0]->channel->setPan(1.0f));

	//delete mixMatrix;

	------------------------

		// Update Listener
	//system->set3DListenerAttributes(0, &listener->Pos, nullptr, nullptr, nullptr);
//	std::cout << "CAMPOS: " << listener->Pos.x << " " << listener->Pos.y << " " << listener->Pos.z << "\t";

	------------------------


	ValidityCheck(speakers[0]->channel->setPan(-1.0f));

	------------------------








*/

#endif

