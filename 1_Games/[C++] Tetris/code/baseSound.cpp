#include "preCompiled.h"
#include "baseSound.h"

AudioDevicePtr baseSound::musicDevice = OpenDevice();

float baseSound::volumeSound = 1.f, baseSound::volumeMusic = 0.5f;


baseSound::baseSound(){

}


baseSound::~baseSound(){
	if (currentMusic != NULL) {
		this->currentMusic->stop();
		currentMusic->unref();
	}
}
