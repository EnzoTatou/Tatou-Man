#ifndef WINDOW_MANAGER__HPP
#define WINDOW_MANAGER__HPP

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

#define WINDOW_STYLE sf::Style::Close
#define WINDOW_NAME "Tatou-Man"
#define ICON_PATH "Data/Sprite/Icon.png"
#define FPS 60

/// <summary>
/// Constructor window function, set the name, the icon and the size of the window.
/// Modifie the defines in WindowManager header to set a new name and icon
/// </summary>
/// <param name="_window"> : Window we gonna define</param>
/// <param name="_windowSize"> : Size of the window</param>
void InitWindow(sf::RenderWindow&, sf::Vector2u);

void SetWindowIcon(sf::RenderWindow&, const std::string&);

#endif