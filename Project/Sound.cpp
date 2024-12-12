#include "Sound.hpp"

sf::Sound CreateSound(const std::string _filePath)
{
	sf::SoundBuffer* buffer = new sf::SoundBuffer;
	sf::Sound newSound;

	if (!buffer->loadFromFile(_filePath))
	{
		std::cerr << "Couldn't create buffer : " << _filePath << "." << std::endl;
		return newSound;
	}

	newSound.setBuffer(*buffer);
	newSound.setVolume(DEFAULT_SOUND_VOLUME);

	return newSound;
}

void PlaySoundOnRepeat(sf::Sound& _sound)
{
	if (_sound.getStatus() == STOPPED || _sound.getStatus() == PAUSED)
	{
		_sound.play();
	}
}