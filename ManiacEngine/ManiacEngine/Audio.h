#pragma once

// Credit : https://www.youtube.com/watch?v=vKwDGQXL29U

#include <SDL_mixer.h>
#include <string>
#include <map>

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
	void play(int loop = 0);
	void pause();
	void stop();
	void resume();
private:
	Mix_Music* m_music = nullptr;
};

class AudioEngine {
	public:
		AudioEngine();
		~AudioEngine();

		void init();
		void destroy();

		SoundEffect loadSoundEffect(const std::string& filePath);
		Music loadMusic(const std::string& filePath);

	private:
		bool isInit;

		std::map<std::string, Mix_Chunk*> m_effectMap;
		std::map<std::string, Mix_Music*> m_musicMap;
};