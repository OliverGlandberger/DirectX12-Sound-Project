#include "SoundManager.hpp"

#include <stdio.h>
#include <iostream>

SoundManager::SoundManager()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&system);
	result = this->system->init(512, FMOD_INIT_NORMAL, 0);

	if (result != FMOD_OK)
	{
		std::cout << "ERROR: FMOD::System did not initialize correctly!" << "\n";
	}
	else
	{
		if (headache) {
			std::string fileName = "../assets/sounds/WhereAmIGoing.ogg";
			result = this->system->createSound(fileName.c_str(), FMOD_LOOP_NORMAL, nullptr, &this->sounds[0]);
			result = this->system->playSound(this->sounds[0], nullptr, false, nullptr);
		}
	}
}

SoundManager::~SoundManager()
{

}

void SoundManager::update()
{
	if (headache) {
		this->system->update();
	}
}