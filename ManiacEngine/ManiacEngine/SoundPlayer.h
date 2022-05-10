#pragma once
#include "Audio.h"
#include <vector>
using namespace std;
class SoundPlayer {
private:
	static SoundPlayer* instance;
	vector<Music> _activeSounds;
	AudioEngine* _audioEngine; 
public:
	SoundPlayer();
	static SoundPlayer* GetInstance();

	void PlaySound(string soundPath);  
	void PlayMusic(string musicPath,int loop = 0);
	void StopSound(string soundTag);
	void ClearSound();

 
};