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

public:
	Game();
	~Game();

	void MainMenu(sf::RenderWindow& window, int &screenWidth, int &screenHeight, sf::Vector2f &waterScreenPos);
	void GameOverScreen(sf::RenderWindow& window, int &score);
	// Runs game
	void Run(sf::RenderWindow& window, int &screenWidth, int &screenHeight, sf::Vector2f &waterScreenPos);
};

