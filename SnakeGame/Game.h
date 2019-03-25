#pragma once
#include <SFML/Graphics.hpp>
#include "Collectable.h"
#include <vector>

enum class gameState
{
	menu,
	singlePlayer,
	aiPlayer,
	gameOver,
	gameWon,
};

class Game
{
protected:
	std::vector<Collectable*>collectableItems;
	int activeCollectables = 0;
	int maxActiveCollectables = 5;

	int waterLeak = 0;

	gameState currentState = gameState::menu;

	// Consider moving this to AISnake.h
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

	int playerSnakeScore = 0;

public:
	Game();
	~Game();

	void Update(sf::RenderWindow& window, int &screenWidth, int &screenHeight, sf::Vector2f &waterScreenPos);
	void MainMenu(sf::RenderWindow& window, int &screenWidth, int &screenHeight, sf::Vector2f &waterScreenPos);
	void GameOverScreen(sf::RenderWindow& window);
	void GameWonScreen(sf::RenderWindow& window);
	// Runs game
	void Run(sf::RenderWindow& window, int &screenWidth, int &screenHeight, sf::Vector2f &waterScreenPos);
	void AIRun(sf::RenderWindow& window, int &screenWidth, int &screenHeight, sf::Vector2f &waterScreenPos);
};

