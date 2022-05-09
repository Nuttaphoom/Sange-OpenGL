#include "SoundPlayer.h"

SoundPlayer* SoundPlayer::instance = nullptr;

SoundPlayer::SoundPlayer() {
	_audioEngine = AudioEngine::GetInstance();
}

SoundPlayer* SoundPlayer::GetInstance(){
	if (instance == nullptr)
	{
		instance = new SoundPlayer() ;
	}

	return instance;
}
 
void SoundPlayer::ClearSound() {
	for (int i = _activeSounds.size() - 1; i >= 0 ; i--) {
 		_activeSounds[i].stop();
		_activeSounds.erase(_activeSounds.begin() + i);
	}
}

void  SoundPlayer::PlaySound(string soundPath) {
 
	Music newSound = _audioEngine->loadMusic(soundPath);
	newSound.play();

	_activeSounds.push_back(newSound);
	
}
void  SoundPlayer::StopSound(string soundTag) {
	for (int i = 0; i < _activeSounds.size(); i++) {
		if (_activeSounds[i].isSameTag(soundTag)) {
			_activeSounds[i].stop();
			_activeSounds.erase(_activeSounds.begin() + i);
			break;
		}
	}
}