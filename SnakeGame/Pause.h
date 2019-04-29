#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Pause
{
protected:
	sf::Font font;
	sf::Text pauseText;
	sf::Text resumeText;
	sf::Text quitText;

	int fontSize = 50;
	sf::Color fontColor = sf::Color::Red;

public:
	Pause();
	~Pause();

	void Render(sf::RenderWindow& window);
};

