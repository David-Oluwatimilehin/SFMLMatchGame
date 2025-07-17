#include "SoundManager.h"
#include <iostream>

SoundManager::~SoundManager()
{
	for (auto i : m_soundMap)
		delete(i.second);

	m_soundMap.clear();
	m_musicMap.clear();
}


bool SoundManager::LoadSound(const std::string& filePath, const std::string& soundName, float pitch, float volume)
{
	if (m_soundMap.count(soundName) > 0){
		std::cout << "The sound " << soundName << " has already been loaded\n";
		return false;
	}

	if (!m_soundBuffer.loadFromFile(filePath)) {
		std::cout << "The sound " << soundName << " can't be loaded\n";
		return false;
	}

	sf::Sound newSound(m_soundBuffer);
	newSound.setPitch(pitch);
	newSound.setVolume(volume);

	m_soundMap.insert({ soundName, new sf::Sound(newSound) });
	std::cout << "The sound " << soundName << " is loaded :)\n";
	return true;

}


bool SoundManager::LoadMusic(const std::string& filePath, const std::string& songName, float soundPitch, float volume, bool isLooping)
{
	if (m_musicMap.count(songName) > 0) {
		std::cout << "The music " << songName << " has already been loaded\n";
		return false;
	}

	auto newMusic = std::make_unique<sf::Music>();
	if (!newMusic->openFromFile(filePath)) {
		// Handle error (e.g., log it)
		std::cout << "Song couldn't be loaded\n";
		return false;
	}

	newMusic->setPitch(soundPitch);
	newMusic->setVolume(volume);
	newMusic->setLooping(isLooping);
	m_musicMap[songName] = std::move(newMusic);

	//m_musicMap.insert({ songName, sf::Music() });
	//m_musicMap[songName] = std::move(newMusic);
	std::cout << "The song " << songName << "  has been loaded\n";
	return true;
}

void SoundManager::StopSong(const std::string& songName)
{
	auto it = m_musicMap.find(songName);
	if (it != m_musicMap.end()) {
		it->second->setLooping(false);
		it->second->stop();
	}
	else {
		std::cout << " The song " << songName << " does not exist.\n";
	}
}

void SoundManager::PauseSong(const std::string& songName)
{
	auto it = m_musicMap.find(songName);
	if (it != m_musicMap.end()) {
		it->second->setLooping(false);
		it->second->pause();
	}
	else {
		std::cout << " The song " << songName << " does not exist.\n";
	}
	
}


void SoundManager::PlaySound(const std::string& soundName)
{
	if (m_soundMap.count(soundName) == 0) {
		std::cout << "The sound " << soundName << " doesn't exist, so can't be played\n";
		return;
	}

	m_soundMap[soundName]->play();	 

}


void SoundManager::PlaySong(const std::string& songName)
{
	auto it = m_musicMap.find(songName);
	if (it != m_musicMap.end()) {
		// If storing by value:
		
		// If storing unique_ptr:
		it->second->play();
	}
	else {
		std::cout << " The song " << songName << " does not exist.\n";
	}

}


