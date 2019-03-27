#pragma once
#include <SFML/Graphics.hpp>
#include "Collectable.h"
#include "AISnake.h"
#include <vector>

enum class gameState
{
	menu,
	singlePlayer,
	aiPlayer,
	gameOver,
	gameWon,
	restart,
};

class Game
{
protected:
	bool isRestarting = false;

	std::vector<Collectable*>collectableItems;
	int activeCollectables = 0;
	int maxActiveCollectables = 5;

	int waterLeak = 0;

	gameState currentState = gameState::menu;

	std::vector<AISnake*>aiSnakes;
	int aiPlayers = 2;

	// Consider moving this to AISnake.h UPDATE: HAS TO MOVE BECAUSE AI SNAKES NOW IN VECTOR, EACH SNAKE NEEDS INDIVIDUAL VALUES
	std::vector<int> AICollectableDistance;
	int xDistance = 0;
	int yDistance = 0;
	int distance = 0;
	int closestValue = 0;
	int closestValuePos = 0;
	int secondClosestValue = 0;
	int secondClosestValuePos = 0;

	sf::Vector2f AITargetCollectable;
	int xTargetDistance = 0;
	int yTargetDistance = 0;

	int playerSnakeScore = 0;

public:
	Game();
	~Game();

	void Update(sf::RenderWindow& window, const int &screenWidth, const int &screenHeight, sf::Vector2f &waterScreenPos);
	void MainMenu(sf::RenderWindow& window, const int &screenWidth, const int &screenHeight, sf::Vector2f &waterScreenPos); // gameState::menu
	void GameOverScreen(sf::RenderWindow& window); // gameState::gameOver
	void GameWonScreen(sf::RenderWindow& window); // gameState::gameWon
	void Restart(sf::RenderWindow& window);

	// Runs game
	void Run(sf::RenderWindow& window, const int &screenWidth, const int &screenHeight, sf::Vector2f &waterScreenPos); // gameState::singlePlayer
	void AIRun(sf::RenderWindow& window, const int &screenWidth, const int &screenHeight, sf::Vector2f &waterScreenPos); // gameState::aiPlayer

	// Returns state
	gameState GetState();
	bool GetRestart();
};

