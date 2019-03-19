#pragma once
#include <SFML/Graphics.hpp>
#include "Collectable.h"
#include <vector>

class Game
{
protected:
	std::vector<Collectable*>collectableItems;
	int activeCollectables = 0;
	int maxActiveCollectables = 5;

	int waterLeak = 0;

	std::vector<int> AICollectableDistance;
	int xDistance = 0;
	int yDistance = 0;
	int distance = 0;
	int closestValue = 0;
	int closestValuePos = 0;
	int secondClosestValue = 0;
	int secondClosestValuePos = 0;
	int thirdClosestValue = 0;
	int thirdClosestValuePos = 0;

	sf::Vector2f AITargetCollectable;
	int xTargetDistance = 0;
	int yTargetDistance = 0;

public:
	Game();
	~Game();

	void MainMenu(sf::RenderWindow& window, int &screenWidth, int &screenHeight, sf::Vector2f &waterScreenPos, int &score);
	void GameOverScreen(sf::RenderWindow& window, int &score);
	// Runs game
	void Run(sf::RenderWindow& window, int &screenWidth, int &screenHeight, sf::Vector2f &waterScreenPos);
	void AIRun(sf::RenderWindow& window, int &screenWidth, int &screenHeight, sf::Vector2f &waterScreenPos, int &score);
};

