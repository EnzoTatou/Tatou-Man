#ifndef KEY__HPP
#define KEY__HPP

#include "SFML/Graphics.hpp"

// The keyboard's data in the current and the previous frame
struct KeyData
{
    bool currentKeyState[sf::Keyboard::KeyCount]; // curent frame key state
    bool previousKeyState[sf::Keyboard::KeyCount]; // previous frame key state
};

/// <summary>
/// Update all the key state in the current and previous frame
/// </summary>
/// <param name="_keyData"> : Data to update </param>
void UpdateKeyData(KeyData& _keyData);

/// <summary>
/// Check if key was pressed in the current frame
/// </summary>
/// <param name="_key"> : Key to check</param>
/// <param name="_keyData"> : Where all the key data is stored</param>
/// <returns>True if the key was pressed, false otherwise</returns>
bool IsKeyPressed(sf::Keyboard::Key _key, KeyData& _keyData);

/// <summary>
/// Check if key was released in the current frame
/// </summary>
/// <param name="_key"> : Key to check</param>
/// <param name="_keyData"> : Where all the key data is stored</param>
/// <returns>True if the key was released, false otherwise</returns>
bool IsKeyReleased(sf::Keyboard::Key _key, KeyData& _keyData);

/// <summary>
/// Check if key was held in the current frame.
/// This function do the same thing as sf::KeyBoard::isKeyPressed
/// but for the sake of readability we use this one.
/// </summary>
/// <param name="_key"> : Key to check</param>
/// <param name="_keyData"> : Where all the key data is stored</param>
/// <returns>True if the key was held, false otherwise</returns>
bool IsKeyHeld(sf::Keyboard::Key _key, KeyData& _keyData);

#endif // !KEY__HPP