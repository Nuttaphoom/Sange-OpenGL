#include "SoundPlayer.h"
#include <iostream>
using namespace std; 

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

void SoundPlayer::PlayMusic(string musicPath,int loop) {
	Music newSound = _audioEngine->loadMusic(musicPath);
	newSound.play(loop);
	

	_activeSounds.push_back(newSound);
}

void  SoundPlayer::PlaySound(string soundPath) {
 
	SoundEffect newSound = _audioEngine->loadSoundEffect(soundPath);
	newSound.play();	
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