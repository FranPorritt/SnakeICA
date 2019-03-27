#pragma once
#include "Snake.h"

class AISnake : public Snake
{
private:
	bool isDirectionSet = false;
	// Determines chance of snake colliding with the edge of the screen, the higher the number the less chance of hitting the wall.
	int edgeChance = 5;

public:
	AISnake(sf::Vector2f screenPosArg, sf::Color colorArg, float radiusArg);
	~AISnake();

	void Move() override;
	void Update(const int &screenWidth, const int &screenHeight, sf::RenderWindow & window, sf::Vector2f &waterScreenPos) override;

	// Sets direction based on x position
	void AboveWater(const int &screenWidth) override;
	void BelowWater() override;

	// Sets direction
	void CollectableNorth();
	void CollectableSouth();
	void CollectableEast();
	void CollectableWest();
	sf::Vector2f SetRandomDestination();

	// Clears segment list
	void Dead(sf::RenderWindow & window);
};

