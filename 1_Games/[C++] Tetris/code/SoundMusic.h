#ifndef _MUSIC_SOUND_H_
#define _MUSIC_SOUND_H_

#include "baseSound.h"
class SoundMusic :
	public baseSound
{
public:
	SoundMusic();
	~SoundMusic();

	void Play();
	void Play(const char *path);
	void Stop();
};

#endif