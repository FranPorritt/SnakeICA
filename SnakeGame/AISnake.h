#pragma once
#include "Snake.h"

class AISnake : public Snake
{
public:
	AISnake(sf::Vector2f screenPosArg, sf::Color colorArg, float radiusArg);
	~AISnake();

	void Move() override;
	void Update(int &screenWidth, int &screenHeight, sf::RenderWindow & window, sf::Vector2f &waterScreenPos) override;
	void CollectableNorth();
	void CollectableSouth();
	void CollectableEast();
	void CollectableWest();
	void Dead(sf::RenderWindow & window, int &score) override;
};

