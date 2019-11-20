#include "UI.h"
#include <iostream>

UI::UI()
{
	highScore = 0;
}

UI::~UI()
{
}

void UI::GameEnd(sf::RenderWindow& window, int& playerSnakeScore)
{
	if (!font.loadFromFile("ka1.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	// Score Text
	scoreText.setFont(font);
	scoreText.setCharacterSize(50);
	scoreText.setPosition(500, 250);
	scoreText.setString("SCORE: " + std::to_string(playerSnakeScore));
	scoreText.setFillColor(fontColor);
	scoreText.setOrigin(floor(scoreText.getLocalBounds().width / 2), floor(scoreText.getLocalBounds().height / 2));

	// Restart Text
	restartText.setFont(font);
	restartText.setCharacterSize(35);
	restartText.setPosition(500, 600);
	restartText.setString("PRESS SPACE TO RESTART");
	restartText.setFillColor(fontColor);
	restartText.setOrigin(floor(restartText.getLocalBounds().width / 2), floor(restartText.getLocalBounds().height / 2));

	// Quit Text
	quitText.setFont(font);
	quitText.setCharacterSize(35);
	quitText.setPosition(500, 700);
	quitText.setString("PRESS Q TO QUIT");
	quitText.setFillColor(fontColor);
	quitText.setOrigin(floor(quitText.getLocalBounds().width / 2), floor(quitText.getLocalBounds().height / 2));
	
	// Render
	window.draw(scoreText);
	window.draw(restartText);
	window.draw(quitText);
}

void UI::GameOver(sf::RenderWindow& window)
{
	if (!font.loadFromFile("ka1.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	// Lose Text
	loseText.setFont(font);
	loseText.setCharacterSize(85);
	loseText.setPosition(500, 100);
	loseText.setString("GAME OVER");
	loseText.setFillColor(fontColor);
	loseText.setOrigin(floor(loseText.getLocalBounds().width / 2), floor(loseText.getLocalBounds().height / 2));

	window.draw(loseText);
}

void UI::GameWon(sf::RenderWindow& window)
{
	if (!font.loadFromFile("ka1.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	// Win Text
	winText.setFont(font);
	winText.setCharacterSize(85);
	winText.setPosition(500, 100);
	winText.setString("GAME WON");
	winText.setFillColor(fontColor);
	winText.setOrigin(floor(winText.getLocalBounds().width / 2), floor(winText.getLocalBounds().height / 2));

	window.draw(winText);
}

void UI::HighScore(sf::RenderWindow& window, int& playerSnakeScore)
{
	input.open("highScore.txt.");
	if (output.fail())
	{
		std::cerr << "Could not open file for write" << std::endl;
	}
	input >> highScore;
	input.close();

	if (highScore < playerSnakeScore)
	{
		output.open("highScore.txt");
		if (output.fail())
		{
			std::cerr << "Could not open file for write" << std::endl;
		}
		output << playerSnakeScore << std::endl;
		output.close();
	}

	if (!font.loadFromFile("ka1.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	// High Score Text
	highScoreText.setFont(font);
	highScoreText.setCharacterSize(50);
	highScoreText.setPosition(500, 350);
	highScoreText.setString("HIGH SCORE: " + std::to_string(highScore));
	highScoreText.setFillColor(sf::Color::Red);
	highScoreText.setOrigin(floor(highScoreText.getLocalBounds().width / 2), floor(highScoreText.getLocalBounds().height / 2));

	window.draw(highScoreText);
}

void UI::Menu(sf::RenderWindow& window, const int &screenWidth, const int &screenHeight)
{
	if (!font.loadFromFile("ka1.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	titleText.setFont(font);
	titleText.setCharacterSize(75);
	titleText.setPosition(screenWidth / 2, screenHeight / 6);
	titleText.setString("SNAKE");
	titleText.setFillColor(sf::Color::Green);
	titleText.setOrigin(floor(titleText.getLocalBounds().width / 2), floor(titleText.getLocalBounds().height / 2));

	// Single Player Text
	singleText.setFont(font);
	singleText.setCharacterSize(30);
	singleText.setPosition(screenWidth / 4, 350);
	singleText.setString("SINGLE \n PLAYER");
	singleText.setFillColor(fontColor);
	singleText.setOrigin(floor(singleText.getLocalBounds().width / 2), floor(singleText.getLocalBounds().height / 2));

	// Player VS AI Text
	aiText.setFont(font);
	aiText.setCharacterSize(30);
	aiText.setPosition(screenWidth * 0.75, 350);
	aiText.setString("PLAYER \n VS AI \n 1 \t 2 \t 3");
	aiText.setFillColor(fontColor);
	aiText.setOrigin(floor(aiText.getLocalBounds().width / 2), floor(aiText.getLocalBounds().height / 2));

	// Start Text
	startText.setFont(font);
	startText.setCharacterSize(25);
	startText.setPosition(500, 650);
	startText.setString("PRESS SPACE TO START");
	startText.setFillColor(fontColor);
	startText.setOrigin(floor(startText.getLocalBounds().width / 2), floor(startText.getLocalBounds().height / 2));

	// Quit text
	quitMenuText.setFont(font);
	quitMenuText.setCharacterSize(25);
	quitMenuText.setPosition(500, 700);
	quitMenuText.setString("PRESS Q TO QUIT");
	quitMenuText.setFillColor(fontColor);
	quitMenuText.setOrigin(floor(quitMenuText.getLocalBounds().width / 2), floor(quitMenuText.getLocalBounds().height / 2));
	
	// Render
	window.draw(titleText);
	window.draw(singleText);
	window.draw(aiText);
	window.draw(startText);
	window.draw(quitMenuText);
}