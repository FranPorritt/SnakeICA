#pragma once
#include <SFML/Graphics.hpp>

class Water
{
protected:
	sf::Vector2f waterScreenPos = { 0,40 };
	sf::Color color;
	sf::Vector2f waterSize;

	const float leakRate = 20.0f;
	const float menuLeakRate = 0.05f;

public:
	Water(sf::Color colorArg, sf::Vector2f waterSizeArg);
	~Water();

	// Draws water
	void Render(sf::RenderWindow& window);
	// Reduces water
	void Leak();

	// Menu functions
	void MenuLeak();
	void MenuPos();

	// Returns waterScreenPos
	sf::Vector2f GetScreenPos();
};

