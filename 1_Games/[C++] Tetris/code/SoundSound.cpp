#include "preCompiled.h"
#include "SoundSound.h"


SoundSound::SoundSound(){

}


SoundSound::~SoundSound(){
}

void SoundSound::Play(const char *path) {
	if (musicDevice != NULL) {
		currentMusic = OpenSound(musicDevice, path, true);
		currentMusic->setVolume(volumeSound);
		currentMusic->play();
	}
}

void SoundSound::Stop() {
	if (musicDevice != NULL)
		this->currentMusic->stop();
}