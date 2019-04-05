#pragma once
#include <SFML/Graphics.hpp>
#include "Collectable.h"
#include "AISnake.h"
#include "MenuSnake.h"
#include <vector>

enum class gameState
{
	playerSelect,
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
	bool gameStarting = false;

	std::vector<Collectable*>collectableItems;
	int maxActiveCollectables = 5;

	int waterLeak = 0;

	gameState currentState = gameState::playerSelect;

	// Player Select Menu
	int currentSelection = 0;
	int wiggleTimer = 10;
	int wiggleCount = 0;
	std::vector<MenuSnake*>singleSnakeBody;
	std::vector<MenuSnake*>optionSnakeBody;

	std::vector<AISnake*>aiSnakes;
	int aiPlayers = 0;
	int activeAI = aiSnakes.size();
	bool allAIDead = false;
	sf::Vector2f aiHeadPos;
	int pathfindingSteps = 4;

	// AI Snake Pathfinding values
	int xDistance = 0;
	int yDistance = 0;
	int distance = 0;

	int playerSnakeScore = 0;

public:
	Game();
	~Game();

	void Update(sf::RenderWindow& window, const int &screenWidth, const int &screenHeight, sf::Vector2f &waterScreenPos);
	void PlayerSelectScreen(sf::RenderWindow& window, const int &screenWidth, const int &screenHeight, sf::Vector2f &waterScreenPos); // gameState::playerSelect
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

