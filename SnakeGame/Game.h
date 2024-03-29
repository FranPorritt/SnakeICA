#pragma once
#include <SFML/Graphics.hpp>
#include "Collectable.h"
#include "AISnake.h"
#include "MenuSnake.h"
#include <vector>
#include <iostream>
#include <fstream>

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
	gameState currentState = gameState::playerSelect;

	std::vector<MenuSnake*>playerSnakeBody;
	std::vector<MenuSnake*>AI1SnakeBody;
	std::vector<MenuSnake*>AI2SnakeBody;
	std::vector<MenuSnake*>AI3SnakeBody;
	std::vector<AISnake*>aiSnakes;
	std::vector<Collectable*>collectableItems;

	sf::Vector2f aiHeadPos;
	sf::Vector2f playerHeadPos;
	sf::Vector2f airPos[3] = { {300, 10}, {450,10}, {600,10} };
	
	sf::Color color[3] = { sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan };

	float airLeft = 0;

	int aiPlayers = 0;
	int activeAI = aiSnakes.size();
	int maxActiveCollectables = 5;

	int playerSnakeScore = 0;
	int waterLeak = 0;	

	// Player Select Menu
	int currentSelection = 0;
	int wiggleTimer = 10;
	int wiggleCount = 0;

	// AI Snake Pathfinding values
	int xDistance = 0;
	int yDistance = 0;
	int distance = 0; 	

	// Pause
	bool isPaused = false;
	bool isRestarting = false;
	bool gameStarting = false;

	bool allAIDead = false;

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

	void DisplayAIAir(sf::RenderWindow& window, sf::Vector2f &airPos, sf::Color &color);

	// Returns state
	gameState GetState();
	bool GetRestart();
};

