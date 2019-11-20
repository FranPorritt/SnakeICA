#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

class UI
{
protected:
	sf::Font font;

	sf::Text scoreText; 
	sf::Text highScoreText;
	sf::Text restartText;
	sf::Text quitText;

	sf::Text loseText;
	sf::Text winText;

	sf::Text titleText;
	sf::Text singleText;
	sf::Text aiText;
	sf::Text startText;
	sf::Text quitMenuText;


	sf::Color fontColor = sf::Color::Red;

	int highScore = 0;
	std::ofstream output;
	std::ifstream input;

public:
	UI();
	~UI();
	
	// Displays consistent end game UI -- Score, restart, quit
	void GameEnd(sf::RenderWindow& window, int& playerSnakeScore); 
	// Displays losing specific UI
	void GameOver(sf::RenderWindow& window); 
	// Displays winning specific UI
	void GameWon(sf::RenderWindow& window); 
	// High score
	void HighScore(sf::RenderWindow& window, int& playerSnakeScore);
	// Player Select UI
	void Menu(sf::RenderWindow& window, const int &screenWidth, const int &screenHeight);
};

