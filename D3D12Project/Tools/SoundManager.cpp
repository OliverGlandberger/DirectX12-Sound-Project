#include "SoundManager.hpp"

#include <stdio.h>
#include <iostream>
#include "../Tools/Locator.h"
#include <thread>

// Allocates an array of T with Size where every index is equal to pValue
template<typename T>
T* *initAs(const int size, T* pValue) {
	T* *arr = new T*[size];
	if (pValue == nullptr) {
		for (size_t i = 0; i < size; i++)
		{
			arr[i] = nullptr;
		}
	}
	else {
		for (size_t i = 0; i < size; i++)
		{
			arr[i] = new T(*pValue);
		}
	}

	delete pValue;
	return arr;
};


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

void SoundManager::playAllSounds(float* *pVolumes)
{
	for (size_t i = 0; i < SPEAKERS; i++)
	{
		speakers[i]->play(this->system, pVolumes[i]);
	}
	delete pVolumes;
}

void SoundManager::playAmbience(float* *pVolumes)
{
	ambience->play(this->system, pVolumes[0]);
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
	this->playAllSounds(initAs<float>(SPEAKERS, new float(0.0f)));

	// Start playing Ambience
	this->ambience->play(this->system, new float(0.05));
	ValidityCheck(this->ambience->channel->setMode(FMOD_LOOP_NORMAL));	// Loop ambience
}

SoundManager::~SoundManager()
{
	this->system->close();
	delete this->listener;
	delete this->ambience;

	for (size_t i = 0; i < SPEAKERS; i++)
	{
		delete speakers[i];
	}
	for (size_t i = 0; i < EVENTS; i++)
	{
		delete events[i];
	}
}

void SoundManager::panRight()
{
	events[1]->play(this->system, nullptr);
}

void SoundManager::panLeft()
{	
	events[0]->play(this->system);
}

void SoundManager::update()
{
	// Update Speakers based on distance to listener
	for (size_t i = 0; i < SPEAKERS; i++)
	{
		speakers[i]->updateVolume(listener->Pos);
	}

	// Update the system according to all changes made to channels.
	this->system->update();
}