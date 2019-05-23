#include "SoundStruct.h"
#include <iostream>

void ValidityCheck(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		throw;
	}
}


float SoundStruct::abs(FMOD_VECTOR vector)
{
	float total{ 0 };

	total += pow(vector.x, 2);
	total += pow(vector.y, 2);
	total += pow(vector.z, 2);
	total = sqrt(total);

	return total;
}

SoundStruct::SoundStruct(bool listener)
{
	// Do nothing in particular
}

SoundStruct::SoundStruct(std::string fileName, FMOD::Sound * sound, FMOD::Channel * channel, FMOD_VECTOR pos, FMOD_VECTOR velocity, FMOD_VECTOR forward, FMOD_VECTOR up)
{
	this->fileName = fileName;
	this->sound = sound;
	this->channel = channel;
	this->Pos = pos;
	this->Velocity = velocity;
	this->Forward = forward;
	this->Up = up;
}

SoundStruct::~SoundStruct()
{

}



void SoundStruct::play(FMOD::System *system)
{
	FMOD_RESULT result;
	ValidityCheck(system->createStream(	// Stream|Sound
		this->fileName.c_str(),
		FMOD_2D,
		nullptr,
		&this->sound
	));
	ValidityCheck(system->playSound(		// Start Playing
		this->sound,
		nullptr,
		false,
		&this->channel
	));
	//ValidityCheck(this->channel->set3DAttributes(	// Set basic Attributes
	//	&this->Pos,
	//	&this->Velocity
	//));
}

void SoundStruct::updateVolume(FMOD_VECTOR listenerPos)
{
	// Calculate distanceVector
	FMOD_VECTOR distanceVector{ 0 };
	distanceVector.x = listenerPos.x - Pos.x;
	distanceVector.y = listenerPos.y - Pos.y;
	distanceVector.z = listenerPos.z - Pos.z;
	
	// Calculate distance to listener
	float distance = abs(distanceVector);

	// Change current volume based on logarithmic math
	if ((baseVolume / (distance * distanceFactor)) > 1) {
		this->channel->setVolume(1);
	}
	else {
		this->channel->setVolume(baseVolume / (distance * distanceFactor));
	}


}

void SoundStruct::calculateStereoPan()
{

}