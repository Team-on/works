#ifndef _BASE_SOUND_H_
#define _BASE_SOUND_H_

class baseSound{
public:
	static float volumeSound, volumeMusic;

protected:
	static AudioDevicePtr musicDevice;
	OutputStreamPtr currentMusic;

public:
	baseSound();
	virtual ~baseSound();

	virtual void Play(const char *path) = 0;
	virtual void Stop() = 0;
};

#endif