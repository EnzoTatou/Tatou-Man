#ifndef SOUND_HPP
#define SOUND_HPP

#include <iostream>
#include <deque>
#include "SFML/Audio.hpp"

#define DEFAULT_SOUND_VOLUME 35

enum SoundStatus
{
	STOPPED, // Sound is not playing
	PAUSED,  // Sound is paused
	PLAYING  // Sound is playing
};

sf::Sound CreateSound(const std::string);
void PlaySoundOnRepeat(sf::Sound&);
#endif