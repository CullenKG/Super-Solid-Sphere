#ifndef __AudioCue_H__
#define __AudioCue_H__

class AudioCue
{
private:
	std::vector<SoundObject*> m_Sounds;

public:
	AudioCue();
	~AudioCue();

	void AddSound(SoundObject* sound);
	SoundObject* GetSound();

};

#endif //__AudioCue_H__