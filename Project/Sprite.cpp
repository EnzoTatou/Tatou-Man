#include "Sprite.hpp"

sf::Sprite LoadSprite(const std::string _path, bool _isCentered, sf::Vector2f _size)
{
	sf::Texture* newTexture = new sf::Texture(); // create texture that will not be destroyed after call function
	newTexture->loadFromFile(_path);

	sf::Sprite newSprite;
	newSprite.setTexture(*newTexture);
	newSprite.scale(_size);

	if (_isCentered)
	{
		sf::Vector2u tempTaille = newTexture->getSize();
		sf::Vector2f tempOrigin = sf::Vector2f(tempTaille.x / 2, tempTaille.y / 2);
		newSprite.setOrigin(tempOrigin); // set the origin at the center of the sprite
	}

	return newSprite;
}

void BlitSprite(sf::Sprite& _sprite, sf::RenderWindow& _window, sf::Vector2f _pos, float _angle)
{
	_sprite.setRotation(_angle);
	_sprite.setPosition(_pos);
	_window.draw(_sprite);
}