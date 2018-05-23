#include "preCompiled.h"
#include "SoundMusic.h"


SoundMusic::SoundMusic(){

}


SoundMusic::~SoundMusic(){
}

void SoundMusic::Play() {
	if (currentMusic != NULL && musicDevice != NULL)
		currentMusic->play();
}

void SoundMusic::Play(const char *path) {
	if (musicDevice != NULL) {
		currentMusic = OpenSound(musicDevice, path, true);
		currentMusic->setVolume(volumeMusic);
		currentMusic->setRepeat(true);
		currentMusic->play();
	}
}

void SoundMusic::Stop() {
	if (currentMusic != NULL && musicDevice != NULL)
		this->currentMusic->stop();
}