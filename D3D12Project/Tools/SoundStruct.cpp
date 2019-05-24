#include "SoundStruct.h"
#include <iostream>

#define PI 3.14159265359

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
	//delete this->sound;
//	delete this->channel;
}



void SoundStruct::play(FMOD::System *system, float *volume)
{
	FMOD_RESULT result;
	ValidityCheck(system->createStream(	// Stream|Sound
		this->fileName.c_str(),
		FMOD_2D,
		nullptr,
		&this->sound
	));
	ValidityCheck(system->playSound(	// Start Playing
		this->sound,
		nullptr,
		false,
		&this->channel
	));
	if (volume != nullptr) {			// Set specific starting volume, if we want
		ValidityCheck(this->channel->setVolume(*volume));
	}
	else {
		ValidityCheck(this->channel->setVolume(this->baseVolume));
	}

	delete volume;
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
		ValidityCheck(this->channel->setVolume(1));
	}
	else {
		ValidityCheck(this->channel->setVolume(baseVolume / (distance * distanceFactor)));
	}
}

void SoundStruct::calculateStereoPan(SoundStruct* Listener)
{
	/// 2D-Panning, only needs x(right) and z(forward)
	// Calculate second vector
	FMOD_VECTOR listenerToSource{0};
	listenerToSource.x = this->Pos.x - Listener->Pos.x;
	listenerToSource.z = this->Pos.z - Listener->Pos.z;
											   
	// Calculate dotproduct					   
	float dotProduct = 0;					   
	dotProduct += listenerToSource.x * Listener->Forward.x;
	dotProduct += listenerToSource.z * Listener->Forward.z;

	// Calculate angle which indicates scaling of panning
	float denominator = 0;
	denominator = abs(listenerToSource) + abs(Listener->Forward);
	float angle = acos(dotProduct / denominator) * 180 / PI;

	// Calculate how much we want to pan based on the angle and range[0-1]
	float panFactor = angle / 90; // 90 --> 1, 0-->0
	float padding = 0.5;


	// Calculate vector-relativity to determine left/right (rotate 2nd vector then dot)
	float sideValue = (Listener->Forward.x*-listenerToSource.z) + (Listener->Forward.z*listenerToSource.x);

	if (sideValue > padding) {		// It is on the left side
		this->channel->setPan(1 * angle * panFactor);
		std::cout << "PAN: " << angle * panFactor << " ANGLE: " << angle << "\n";
	}
	else if (sideValue < -1*padding) {	// It is on the right side
		this->channel->setPan(-1 * angle * panFactor);
		std::cout << "PAN: " << angle * panFactor << " ANGLE: " << angle << "\n";
	}
	else{						// It's perpendicular to listeners direction
		this->channel->setPan(0);
		std::cout << "PAN: " << 0 << " ANGLE: " << 0 << "\n";
	}
}