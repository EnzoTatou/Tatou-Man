#include "Definition.hpp"

sf::Text CreateText(sf::Font& _font, const sf::String _string, int _size, sf::Color _color)
{
	sf::Text newText;
	newText.setFont(_font);
	newText.setCharacterSize(_size);

	newText.setFillColor(_color);

	return newText;
}

void SetCenteredString(sf::Text& _text, const sf::String _string)
{
	_text.setString(_string);
	_text.setOrigin(sf::Vector2f((int)_text.getGlobalBounds().width / 2, (int)_text.getGlobalBounds().height / 2));
}

bool IsCollidingRectanglePoint(sf::FloatRect _rect, sf::Vector2f _point)
{
	return (_rect.left < _point.x&&
		_rect.left + _rect.width > _point.x &&
		_rect.top < _point.y &&
		_rect.top + _rect.height > _point.y);
}

bool IsCollidingRectangles(sf::FloatRect _rectA, sf::FloatRect _rectB)
{
	return (_rectA.left < _rectB.left + _rectB.width &&
		_rectA.left + _rectA.width > _rectB.left &&
		_rectA.top < _rectB.top + _rectB.height &&
		_rectA.top + _rectA.height > _rectB.top);
}