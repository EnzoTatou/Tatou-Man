#ifndef SPRITE__HPP
#define SPRITE__HPP
#include "SFML/Graphics.hpp"

/// <summary>
/// Create texture and return sprite, can also automatically centered it and scale it.
/// </summary>
/// <param name="_path"> : Path of the image to load</param>
/// <param name="_isCentered"> : If origin is in the center of texture</param>
/// <param name="_size"> : Scale factor</param>
/// <returns>Sprite copy</returns>
sf::Sprite LoadSprite(const std::string _path, bool _isCentered = true, sf::Vector2f _size = { 1, 1 });

/// <summary>
/// Change position and angle of copy sprite and draw it to the window
/// </summary>
/// <param name="_sprite"> : Copy of sprite to draw</param>
/// <param name="_window"> : Render targer</param>
/// <param name="_pos"> : Position of sprite</param>
/// <param name="_angle"> : Angle of sprite</param>
void BlitSprite(sf::Sprite& _sprite, sf::RenderWindow& _window, sf::Vector2f _pos, float _angle = 0.f);

#endif // !SPRITE__HPP