#pragma once

// Credit : https://www.youtube.com/watch?v=vKwDGQXL29U

#include <SDL_mixer.h>
#include <string>
#include <map>
#include <string>
using namespace std;  
class SoundEffect {
public:
	friend class AudioEngine;
	void play(int loop = 0);
private:
	Mix_Chunk* m_chunk = nullptr;
};

class Music {
public:
	friend class AudioEngine;
	Music() ;
	Music(string soundTag); 
	void play(int loop = 0);
	void pause();
	void stop();
	void resume();
	bool isSameTag(string comparedTag); 
private:
	Mix_Music* m_music = nullptr;
	string soundTag ; 
};

class AudioEngine {
	public:
		float masterVolume = 0.5f;
		float sfxVolume = 1.0f;
		float musicVolume = 0.5f;

		static AudioEngine* instance;
		AudioEngine();
		~AudioEngine();

		void init();
		void destroy();

		void setMastervolume(float masterVol);
		void setsfxVolume(float sfxVol);
		void setMusicVolume(float musicVol);

		static AudioEngine* GetInstance();
		SoundEffect loadSoundEffect(const std::string& filePath);
		Music loadMusic(const std::string& filePath);

	private:
		bool isInit;

		std::map<std::string, Mix_Chunk*> m_effectMap;
		std::map<std::string, Mix_Music*> m_musicMap;
};