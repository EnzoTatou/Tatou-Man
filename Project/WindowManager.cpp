#include "WindowManager.hpp"

void InitWindow(sf::RenderWindow& _window, sf::Vector2u _windowSize)
{
	_window.create(sf::VideoMode(_windowSize.x, _windowSize.y), WINDOW_NAME, WINDOW_STYLE);
	SetWindowIcon(_window, ICON_PATH);
	_window.setFramerateLimit(FPS);
}

void SetWindowIcon(sf::RenderWindow& _window, const std::string& _filePath)
{
	sf::Image tempImage = sf::Image(); // temporary image for loading the file and putting it into window icon
	if (!tempImage.loadFromFile(_filePath))
	{
		std::cerr << "Failed to set window icon. Reason : Unable to get load icon image" << std::endl;
		return;
	}
	sf::Vector2u tempImageSize = tempImage.getSize();
	_window.setIcon(tempImageSize.x, tempImageSize.y, tempImage.getPixelsPtr());
}