#include "GamePCH.h"

AudioCue::AudioCue()
{
}

AudioCue::~AudioCue()
{
	for (auto object : m_Sounds)
		delete object;
}

void AudioCue::AddSound(SoundObject* sound)
{
	m_Sounds.push_back(sound);
}

SoundObject* AudioCue::GetSound()
{
	int randomNumber = rand() % m_Sounds.size();

	return m_Sounds[randomNumber];
}