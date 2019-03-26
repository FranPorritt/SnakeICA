#pragma once
#include <SFML/Graphics.hpp>
#include "Water.h"

class Collectable
{
protected:
	sf::Vector2f screenPos;
	sf::Color color;
	float radius;
	int aliveCheckTime = 4;
	bool aliveFlag = false;
	bool isPickedUp = false;

public:
	Collectable() {}
	Collectable(sf::Vector2f screenPosArg, sf::Color colorArg, float radiusArg);
	~Collectable();

	// Returns if active
	bool Alive();
	// Randomly sets collectable active
	void AliveCheck();

	// Makes collectable inactive and calls NewScreenPos
	void PickedUp(Water& water, int &screenHeight);
	// Draws the collectable
	void Render(sf::RenderWindow& window, int &screenWidth, int &screenHeight);
	// Gets new random screen position
	sf::Vector2f NewScreenPos(sf::Vector2f &screenPos, Water& water, int &screenHeight);
	// Makes sure collectables aren't out of playing field
	void Floating();
	// Returns screen position
	sf::Vector2f GetScreenPos();
};

