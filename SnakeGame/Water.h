#pragma once
#include <SFML/Graphics.hpp>

class Water
{
protected:
	sf::Vector2f waterScreenPos = { 0,20 };
	sf::Color color;
	sf::Vector2f waterSize;

public:
	Water(sf::Color colorArg, sf::Vector2f waterSizeArg);
	~Water();

	// Draws water
	void Render(sf::RenderWindow& window);
	// Reduces water
	void Leak();
	// Returns waterScreenPos
	sf::Vector2f GetScreenPos();
};

