#pragma once
#include <SFML/Audio.hpp>

class SoundManager {
private:
	sf::SoundBuffer m_soundBuffer;
	std::unordered_map<std::string, sf::Sound*> m_soundMap;
	std::unordered_map<std::string, std::unique_ptr<sf::Music>> m_musicMap;

public:
	SoundManager() {};
	~SoundManager();
	bool LoadSound(const std::string& filePath, const std::string& soundName, float pitch, float volume);
	bool LoadMusic(const std::string& filePath, const std::string& songName, float soundPitch, float volume, bool isLooping);

	void StopSong(const std::string& songName);
	void PauseSong(const std::string& songName);

	void PlaySound(const std::string& soundName);
	void PlaySong(const std::string& songName);

};