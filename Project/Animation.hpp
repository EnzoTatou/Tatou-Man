#ifndef ANIMATION__HPP
#define ANIMATION__HPP

#include "Sprite.hpp"
#include <iostream>

struct Animation
{
	sf::Clock clock;
	float time = 0.f;
	float animationTime = 1; // time (in second) taken to make a full animation cycle
	int numberSprite;

	sf::Sprite* spriteArray; // array containing all the frames of the animation
	sf::Sprite* currentSprite; // sprite ptr to display
};

/// <summary>
/// Constructor of animation structure
/// </summary>
/// <param name="_numberSprite"> Number of frame the animation have</param>
/// <param name="_animationTime"> : Time taken to make a full animation cycle</param>
/// <param name="_spriteArray"> : Array containing all the frames of the animation</param>
/// <returns> New animation structure</returns>
Animation CreateAnimation(int _numberSprite, float _animationTime, sf::Sprite* _spriteArray);

/// <summary>
/// Change the sprite ptr depending on animation time and update animation time
/// </summary>
/// <param name="_animation"> : Animation to update</param>
/// <param name="_dt"> : DeltaTime</param>
void UpdateAnimation(Animation& _animation, const float _dt);

/// <summary>
/// Blit current sprite of the animation to the render target
/// </summary>
/// <param name="_animation"> : Animation to display</param>
/// <param name="_pos"> : Position of sprite</param>
/// <param name="_angle"> : Angle of sprite</param>
/// <param name="_window"> : Render target</param>
void DisplayAnimation(Animation& _animation, sf::Vector2f _pos, float _angle, sf::RenderWindow& _window);

#endif // !ANIMATION__HPP