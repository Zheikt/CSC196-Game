#include "AudioSystem.h"

namespace Enginuity
{
	AudioSystem g_audioSystem;

	bool AudioSystem::Initialize()
	{
		FMOD::System_Create(&m_fmodSystem);
		void* extradriverdata = nullptr;
		m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
		return true;
	}
	void AudioSystem::Shutdown()
	{
		for (auto sound : m_sounds) sound.second->release();
		m_sounds.clear();
		m_fmodSystem->close();
		m_fmodSystem->release();
	}
	void AudioSystem::Update()
	{
		m_fmodSystem->update();
	}
	void AudioSystem::AddAudio(const std::string& name, const std::string& filename)
	{
		if (m_sounds.find(name) == m_sounds.end())
		{
			FMOD::Sound* sound = nullptr;
			m_fmodSystem -> createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
			m_sounds[name] = sound;
		}
	}
	void AudioSystem::PlayOneShot(const std::string& name, bool loop)
	{
		auto iter = m_sounds.find(name);
		if (iter != m_sounds.end())
		{
			FMOD::Sound* sound = iter->second;
			sound->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
			FMOD::Channel* channel;
			m_fmodSystem->playSound(sound, 0, false, &channel);
			m_channels[name] = channel;
		}
	}

	void AudioSystem::PlayLoop(const std::string& name)
	{
		auto iter = m_sounds.find(name);
		if (iter != m_sounds.end())
		{
			FMOD::Sound* sound = iter->second;
			sound->setMode(FMOD_LOOP_NORMAL);
			FMOD::Channel* channel;
			m_fmodSystem->playSound(sound, 0, false, &channel);
			m_channels[name] = channel;
		}
	}

	void AudioSystem::StopLoop(const std::string& name)
	{
		auto iter = m_sounds.find(name);
		auto chanIter = m_channels.find(name);
		if (iter != m_sounds.end())
		{
			/*FMOD::Sound* sound = iter->second;
			sound->setMode(FMOD_LOOP_OFF);*/
			FMOD::Channel* channel = chanIter->second;
			channel->stop();
			//m_fmodSystem->playSound(sound, 0, true, &channel);
		}
	}

	bool AudioSystem::IsPlaying(const std::string& name)
	{
		auto iter = m_channels.find(name);
		if (iter != m_channels.end())
		{
			bool* retVal = new bool{ false };
			iter->second->isPlaying(retVal);
			return *retVal;
		}

		return false;
	}
}