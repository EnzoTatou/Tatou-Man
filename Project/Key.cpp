#include "Key.hpp"

void UpdateKeyData(KeyData& _keyData)
{
    for (unsigned int i = 0; i < sf::Keyboard::KeyCount; ++i)
    {
        // Save the keyboard's state from the previous frame
        _keyData.previousKeyState[i] = _keyData.currentKeyState[i];

        // Save the keyboard's state in the current frame
        _keyData.currentKeyState[i] = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);
    }
}

bool IsKeyPressed(sf::Keyboard::Key _key, KeyData& _keyData)
{
    return (_keyData.currentKeyState[_key] && !_keyData.previousKeyState[_key]);
}

bool IsKeyReleased(sf::Keyboard::Key _key, KeyData& _keyData)
{
    return (!_keyData.currentKeyState[_key] && _keyData.previousKeyState[_key]);
}

bool IsKeyHeld(sf::Keyboard::Key _key, KeyData& _keyData)
{
    return _keyData.currentKeyState[_key];
}