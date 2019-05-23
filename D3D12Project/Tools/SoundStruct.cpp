#include "SoundStruct.h"

void ValidityCheck(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		throw;
	}
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

void SoundStruct::calculateStereoPan()
{

}