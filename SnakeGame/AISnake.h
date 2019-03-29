#pragma once
#include "Snake.h"
#include "Collectable.h"

class AISnake : public Snake
{
private:
	bool isDirectionSet = false;
	// Determines chance of snake colliding with the edge of the screen, the higher the number the less chance of hitting the wall.
	int edgeChance = 5;

	// Pathfinding
	std::vector<int> AICollectableDistance;
	int distance = 0;
	int closestValue = 0;
	int closestValuePos = 0;
	int secondClosestValue = 0;
	int secondClosestValuePos = 0;
	int thirdClosestValue = 0;
	int thirdClosestValuePos = 0;
	int fourthClosestValue = 0;
	int fourthClosestValuePos = 0;
	int fifthClosestValue = 0;
	int fifthClosestValuePos = 0;

	sf::Vector2f AITargetCollectable;
	int xTargetDistance = 0;
	int yTargetDistance = 0;

public:
	AISnake(sf::Vector2f screenPosArg, sf::Color colorArg, float radiusArg);
	~AISnake();

	void Move() override;
	void CollectableDistance(int& distance);
	void Pathfinding(std::vector<Collectable*>& collectableItems);
	void Update(const int &screenWidth, const int &screenHeight, sf::RenderWindow & window, sf::Vector2f &waterScreenPos) override;

	// Sets direction based on x position
	void AboveWater(const int &screenWidth) override;
	void BelowWater() override;
	void GoForAir();

	// Sets direction
	void CollectableNorth();
	void CollectableSouth();
	void CollectableEast();
	void CollectableWest();
	sf::Vector2f SetRandomDestination();

	// Clears segment list
	void Dead();
};

