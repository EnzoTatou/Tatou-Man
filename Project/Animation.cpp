#include "Animation.hpp"

int GetCurrentIndexSprite(Animation& _animation)
{
	return _animation.numberSprite * _animation.time / _animation.animationTime;
}

Animation CreateAnimation(int _numberSprite, float _animationTime, sf::Sprite* _spriteArray)
{
	Animation newAnimation;
	newAnimation.numberSprite = _numberSprite;
	newAnimation.animationTime = _animationTime;
	newAnimation.spriteArray = _spriteArray;
	newAnimation.currentSprite = &newAnimation.spriteArray[0]; // set sprite ptr to display

	return newAnimation;
}

void UpdateAnimation(Animation& _animation, const float _dt)
{
	// update time and reset time
	_animation.time = (_animation.time + _dt >= _animation.animationTime ? int(_dt * 10) % int(_animation.animationTime * 10) / 10 : _animation.time + _dt);

	_animation.currentSprite = &_animation.spriteArray[GetCurrentIndexSprite(_animation)];
}

void DisplayAnimation(Animation& _animation, sf::Vector2f _pos, float _angle, sf::RenderWindow& _window)
{
	BlitSprite(*_animation.currentSprite, _window, _pos, _angle);
}