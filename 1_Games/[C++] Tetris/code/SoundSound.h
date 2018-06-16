#ifndef _SOUND_SOUND_H_
#define _SOUND_SOUND_H_

#include "baseSound.h"
class SoundSound :
	public baseSound
{
public:
	SoundSound();
	~SoundSound();

	void Play(const char *path);
	void Stop();
};

#endif