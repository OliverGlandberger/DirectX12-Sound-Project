#include "SoundManager.hpp"

#include <stdio.h>
#include <iostream>
#include "../Tools/Locator.h"
#include <thread>

void SoundManager::initializeSpeakers()
{
	speakers[0] = new SoundStruct{
		"../assets/sounds/WhereAmIGoing.ogg",
		nullptr,
		nullptr,
		{1.3f, -0.6, 4.5},			// First
		{0.0f, 0.0f, 0.0f} ,
		{0, 1, 0} ,
		{0, 0, 1}
	};
	if (SPEAKERS > 1) {
		speakers[1] = new SoundStruct{
			"../assets/sounds/flutebaby.ogg",
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
	}
	events[0] = new SoundStruct{
			"../assets/sounds/SeismicCharge.ogg",
			nullptr,
			nullptr,
			{-1.29632103f, -0.592475712f, -4.45499992f} ,// Last -1.29632103, -0.592475712, -4.45499992
			{0.0f, 0.0f, 0.0f} ,
			{0, 1, 0} ,
			{0, 0, 1}
	};
	events[1] = new SoundStruct{
		"../assets/sounds/ZA_WARUDO.ogg",
		nullptr,
		nullptr,
		{-1.29632103f, -0.592475712f, -4.45499992f} ,// Last -1.29632103, -0.592475712, -4.45499992
		{0.0f, 0.0f, 0.0f} ,
		{0, 1, 0} ,
		{0, 0, 1}
	};
}

void SoundManager::initializeSystem()
{
	ValidityCheck(FMOD::System_Create(&system));

	// Disable automatic stereo panning
	ValidityCheck(system->setSoftwareFormat(191000, FMOD_SPEAKERMODE_STEREO, 2));

	// Set distance scaling for clearer stereo panning
	ValidityCheck(system->set3DSettings(1, 1, 7));

	// Initiate system with settings
	ValidityCheck(this->system->init(512, FMOD_INIT_NORMAL, 0));
}

void SoundManager::playAllSounds()
{
	for (size_t i = 0; i < SPEAKERS; i++)
	{
		speakers[i]->play(this->system);
	}
}

void SoundManager::playAmbience()
{
	ambience->play(this->system);
	ValidityCheck(this->system->createStream(	// Stream|Sound
		ambience->fileName.c_str(),
		FMOD_2D,
		nullptr,
		&ambience->sound
	));
	ValidityCheck(this->system->playSound(		// Start Playing
		ambience->sound,
		nullptr,
		false,
		&ambience->channel
	));
	//ValidityCheck(ambience->channel->setMode(FMOD_2D_HEADRELATIVE));
	ValidityCheck(ambience->channel->setVolume(0.005));
}

SoundManager::SoundManager()
{
	// System Settings
	this->initializeSystem();

	// Listener
	listener = new SoundStruct(true);
	Locator::provide(&listener);

	// Init Speakers
	this->initializeSpeakers();

	// Init Ambience
	this->ambience = new SoundStruct{
		"../assets/sounds/RainThunder.ogg",
		nullptr,
		nullptr,
		{-1.29632103f, -0.592475712f, -4.45499992f},// Last -1.29632103, -0.592475712, -4.45499992
		{0.0f, 0.0f, 0.0f},
		{0, 1, 0},
		{0, 0, 1}
	};



	// Start playing all sounds
	this->playAllSounds();
	for (size_t i = 0; i < SPEAKERS; i++)
	{
		speakers[i]->channel->setVolume(0);
	}

	// Start playing Ambience
//this->playAmbience();

}

SoundManager::~SoundManager()
{

}

void SoundManager::panRight()
{
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

	events[1]->play(this->system);


	//delete mixMatrix;
}

void SoundManager::panLeft()
{
//	ValidityCheck(speakers[0]->channel->setPan(-1.0f));
	events[0]->play(this->system);
}

void SoundManager::update()
{
	// Update Listener
	//system->set3DListenerAttributes(0, &listener->Pos, nullptr, nullptr, nullptr);
//	std::cout << "CAMPOS: " << listener->Pos.x << " " << listener->Pos.y << " " << listener->Pos.z << "\t";


	// Update Speakers based on distance to listener
	for (size_t i = 0; i < SPEAKERS; i++)
	{
		speakers[i]->updateVolume(listener->Pos);
	}

	//FMOD_VECTOR pos = listener->Pos;
	this->system->update();
}