#include "Sound.hpp"

#include "Locator.h"

#include <stdio.h>
#include <iostream>

void Sound::checkResult(FMOD_RESULT _result)
{
	if (_result != FMOD_OK) {
		std::cout << "ERROR!";
		getchar();
	}
}

float Sound::calcVectorDist(FMOD_VECTOR _vector)
{
	float returnValue = sqrt((_vector.x * _vector.x + _vector.y * _vector.y + _vector.z * _vector.z));
	return returnValue;
}

Sound::Sound()
{
	this->result = FMOD::System_Create(&soundSystem);
	this->checkResult(result);

	this->result = this->soundSystem->init(512, FMOD_SPEAKERMODE_STEREO, 0);
	this->checkResult(result);

	this->soundSystem->createStream("../assets/sounds/ambiance_1.ogg", FMOD_3D, 0, &this->ambiance);
	this->checkResult(result);

	this->soundSystem->createStream("../assets/sounds/sound_1.ogg", FMOD_3D, 0, &this->sounds[0]);
	this->checkResult(result);
	this->soundPos[0].x = -1.3187f;
	this->soundPos[0].y = -0.4464f;
	this->soundPos[0].z = -4.5206f;

	this->soundSystem->createStream("../assets/sounds/sound_2.ogg", FMOD_3D, 0, &this->sounds[1]);
	this->checkResult(result);
	this->soundPos[1].x = -0.066f;
	this->soundPos[1].y = -0.3259f;
	this->soundPos[1].z = 0.0253f;

	this->soundSystem->createStream("../assets/sounds/sound_3.ogg", FMOD_3D, 0, &this->sounds[2]);
	this->checkResult(result);
	this->soundPos[2].x = 1.2942f;
	this->soundPos[2].y = -0.4739f;
	this->soundPos[2].z = 4.4659f;

	this->playAllSounds();
}

Sound::~Sound()
{

}

void Sound::playAllSounds()
{
	this->result = this->soundSystem->playSound(this->ambiance, nullptr, false, &this->ambianceChan);
	this->checkResult(result);
	this->ambiance->setMode(FMOD_LOOP_NORMAL);
	this->ambianceChan->setVolume(0.1f);

	for (int i = 0; i < SOUND_COUNT; i++)
	{
		this->result = this->soundSystem->playSound(this->sounds[i], nullptr, false, &this->soundChan[i]);
		this->checkResult(result);
		this->sounds[i]->setMode(FMOD_LOOP_NORMAL);
	}
}

void Sound::update()
{
	XMFLOAT3 cameraPosOriginal;

	XMStoreFloat3(&cameraPosOriginal, Locator::getCamera()->m_cameraPos);
	this->cameraPosNew.x = ((cameraPosOriginal.x + this->cameraPosNew.x) * 0.5f);
	this->cameraPosNew.y = ((cameraPosOriginal.y + this->cameraPosNew.y) * 0.5f);
	this->cameraPosNew.z = ((cameraPosOriginal.z + this->cameraPosNew.z) * 0.5f);

	/// Write-to-console the Camera's current pos
	// std::cout << "x: " << cameraPosOriginal.x;
	// std::cout << "y: " << cameraPosOriginal.y;
	// std::cout << "z: " << cameraPosOriginal.z << "\n";

	for (int i = 0; i < SOUND_COUNT; i++)
	{
		this->soundDistance.x = (this->cameraPosNew.x - this->soundPos[i].x);
		this->soundDistance.y = (this->cameraPosNew.y - this->soundPos[i].y);
		this->soundDistance.z = (this->cameraPosNew.z - this->soundPos[i].z);

		this->tempVectorDistance = this->calcVectorDist(this->soundDistance);

		this->soundChan[i]->setVolume(1.0f/(tempVectorDistance * 60.0f));
	}

	this->soundSystem->update();
}