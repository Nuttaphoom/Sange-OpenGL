#include "Audio.h"
#include <iostream>

AudioEngine* AudioEngine::instance = nullptr;

AudioEngine* AudioEngine::GetInstance()
{
	if (instance == nullptr) {
		instance = new AudioEngine();
	}
	return instance;
}

void SoundEffect::play(int loop)
{
	if (Mix_PlayChannel(-1, m_chunk, loop) == -1)
	{
		std::cout << "Mix_PlayChannel Error " << std::string(Mix_GetError());
	}
}

void AudioEngine::setMusicVolume(float setmusicVol) {
	musicVolume = setmusicVol;
	Mix_VolumeMusic(musicVolume * MIX_MAX_VOLUME);
}

void AudioEngine::setsfxVolume(float sfxVol) {
	sfxVolume = sfxVol;
	Mix_Volume(-1, sfxVolume * MIX_MAX_VOLUME);
}

void AudioEngine::setMastervolume(float masterVol) {
	masterVolume = masterVol;
	Mix_VolumeMusic(masterVolume * MIX_MAX_VOLUME);
	Mix_Volume(-1, masterVolume * MIX_MAX_VOLUME);
	
}
void Music::play(int loop)
{
	Mix_PlayMusic(m_music, loop);
}

void Music::pause()
{
	Mix_PauseMusic();
}

void Music::stop()
{
	Mix_HaltMusic();
}

void Music::resume()
{
	Mix_ResumeMusic();
}

AudioEngine::AudioEngine()
{
}

AudioEngine::~AudioEngine()
{
}

void AudioEngine::init()
{
	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1)
	{
		std::cout << "Mix_Init Error " << std::string(Mix_GetError());
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		std::cout << "Mix_Init Error " << std::string(Mix_GetError());
	}

	isInit = true;
}

void AudioEngine::destroy()
{
	if (isInit)
	{
		isInit = false;
		Mix_Quit();
	}
}

SoundEffect AudioEngine::loadSoundEffect(const std::string & filePath)
{
	//Try to find sound in cache
	auto it = m_effectMap.find(filePath);

	SoundEffect effect;

	if (it == m_effectMap.end())
	{
		//Not found sound in cache
		Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
		if (chunk == nullptr)
		{
			std::cout << "Mix_LoadWAV Error " << std::string(Mix_GetError());
		}
		effect.m_chunk = chunk;
		m_effectMap[filePath] = chunk;
	}
	else
	{
		//Find sound in cache
		effect.m_chunk = it->second;
	}


	return effect;
}

Music AudioEngine::loadMusic(const std::string & filePath)
{
	//Try to find sound in cache
	auto it = m_musicMap.find(filePath);

	Music music;

	if (it == m_musicMap.end())
	{
		//Not found sound in cache
		Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());
		if (mixMusic == nullptr)
		{
			std::cout << "Mix_LoadMUS Error " << std::string(Mix_GetError());
		}
		music.m_music = mixMusic;
		m_musicMap[filePath] = mixMusic;
	}
	else
	{
		//Find sound in cache
		music.m_music = it->second;
	}


	return music;
}
 