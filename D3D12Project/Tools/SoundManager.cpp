#include "SoundManager.hpp"

#include <stdio.h>
#include <iostream>
#include "../Tools/Locator.h"

SoundManager::SoundManager()
{
	FMOD_RESULT result;

	// Listener
	listener = new SoundStruct();
	Locator::provide(&listener);

	// Speakers 
	speakers[0] = new SoundStruct{
		"../assets/sounds/WhereAmIGoing.ogg",
		nullptr,
		nullptr,
		{1.3f, -0.6, 4.5},			// First
		{0.0f, 0.0f, 0.0f} ,
		{0, 1, 0} ,
		{0, 0, 1}
	};
	speakers[1] = new SoundStruct{
		"../assets/sounds/TheDeli5_32PM.ogg",
		nullptr,
		nullptr,
		{-0.0183747206f, -0.30000335f, 0.0f} ,			// Medium -0.0183747206, -0.300003350, 0.000000000,
		{0.0f, 0.0f, 0.0f} ,
		{0, 1, 0} ,
		{0, 0, 1}
	};
	speakers[2] = new SoundStruct{
		"../assets/sounds/humanmusic.ogg",
		nullptr,
		nullptr,
		{-1.29632103f, -0.592475712f, -4.45499992f} ,// Last -1.29632103, -0.592475712, -4.45499992
		{0.0f, 0.0f, 0.0f} ,
		{0, 1, 0} ,
		{0, 0, 1}
	};

	result = FMOD::System_Create(&system);
	result = this->system->init(512, FMOD_INIT_NORMAL, 0);

	if (result != FMOD_OK)
	{
		std::cout << "ERROR: FMOD::System did not initialize correctly!" << "\n";
	}
	else
	{
		if (headache) {
			// System Settings
			system->set3DListenerAttributes(
				0,
				&(listener->Pos),
				&(listener->Velocity),
				&(listener->Forward),
				&(listener->Up)
			);
			system->set3DSettings(1, 1, 7);

			for (size_t i = 0; i < SOUNDS; i++)
			{
				result = this->system->createStream(	// Stream|Sound
					speakers[i]->fileName.c_str(),
					FMOD_3D,
					nullptr,
					&speakers[i]->sound
				);
				result = this->system->playSound(		// Start Playing
					speakers[i]->sound,
					nullptr,
					false,
					&speakers[i]->channel
				);
				speakers[i]->channel->set3DAttributes(	// Set basic Attributes
					&speakers[i]->Pos,
					&speakers[i]->Velocity
				);
				speakers[i]->channel->set3DDistanceFilter(true, 3, 2);	// Distance filter
			}
		}
	}
}

SoundManager::~SoundManager()
{

}

void SoundManager::update()
{
	if (headache) {
		// Update Listener
		system->set3DListenerAttributes(0, &listener->Pos, nullptr, nullptr, nullptr);

		//// Update Speaker0
		//channel0->set3DAttributes()

		//FMOD_VECTOR pos = listener->Pos;
		this->system->update();
		

		//std::cout << "Current Volume: " << volume << " | ListenerPos: " << pos.x << " " << pos.y << " " << pos.z << "\n";
	}
}