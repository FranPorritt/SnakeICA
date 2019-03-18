#include "Game.h"
#include "Snake.h"
#include "Water.h"
#include "AISnake.h"
#include <iostream>

Game::Game()
{
}

Game::~Game()
{
}

void Game::MainMenu(sf::RenderWindow& window, int &screenWidth, int &screenHeight, sf::Vector2f &waterScreenPos)
{
	sf::Font font;
	if (!font.loadFromFile("F25_Bank_Printer.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}
		}

		sf::Text titleText;
		titleText.setFont(font);
		titleText.setCharacterSize(50);
		titleText.setPosition(screenWidth/2 -100, screenHeight/2 - 50);
		titleText.setString("SNAKE");
		titleText.setFillColor(sf::Color::Green);


		sf::Text menuText;
		menuText.setFont(font);
		menuText.setCharacterSize(30);
		menuText.setPosition(300, 500);
		menuText.setString("Press SPACE to play");
		menuText.setFillColor(sf::Color::Red);

		window.draw(titleText);
		window.draw(menuText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Run(window, screenWidth, screenHeight, waterScreenPos);
		}

		window.display();
		window.clear();
	}
}

void Game::GameOverScreen(sf::RenderWindow& window, int &score)
{
	sf::Font font;
	if (!font.loadFromFile("F25_Bank_Printer.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}
		}

		sf::Text gameOverText;
		gameOverText.setFont(font);
		gameOverText.setCharacterSize(50);
		gameOverText.setPosition(350, 325);
		gameOverText.setString("GAME OVER");
		gameOverText.setFillColor(sf::Color::Red);

		sf::Text scoreText;
		scoreText.setFont(font);
		scoreText.setCharacterSize(50);
		scoreText.setPosition(350, 500);
		scoreText.setString("SCORE: " + std::to_string(score));
		scoreText.setFillColor(sf::Color::Red);

		window.draw(gameOverText);
		window.draw(scoreText);

		window.display();
		window.clear();
	}
}

void Game::Run(sf::RenderWindow& window, int &screenWidth, int &screenHeight, sf::Vector2f &waterScreenPos)
{
	sf::Clock clock;
	srand(time(0));
	
	Water* water = new Water(sf::Color::Blue, { (float)screenWidth, (float)screenHeight - 20.0f });
	Snake* playerSnake = new Snake({500,500}, sf::Color::Green, 10.0f);
	AISnake* aiSnake = new AISnake({ 200,500 }, sf::Color::Yellow, 10.0f);
	
	// Creates collectables
	for (int collectableIndex = 0; collectableIndex < maxActiveCollectables; collectableIndex++)
	{
		// Finds random screen position
		float x = (rand() % 50 + 1) * 20;
		float y = (rand() % 36 + 1) * 20;

		// Checks collectable isn't spawning above water
		if (y < water->GetScreenPos().y || y >= screenHeight)
		{
			float y = (rand() % 36 + 1) * 20;
		}

		collectableItems.push_back(new Collectable({ x,y }, sf::Color::Red, 10.0f));
		activeCollectables++;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}
		}			   

		while (clock.getElapsedTime().asMilliseconds() < 200);
		clock.restart();

		water->Render(window);

		playerSnake->Move();
		aiSnake->Move();

	    playerSnake->Update(screenWidth, screenHeight, window, waterScreenPos);
		aiSnake->Update(screenWidth, screenHeight, window, waterScreenPos);

		playerSnake->Render(window);
		aiSnake->Render(window);

		for (Collectable *c : collectableItems)
		{
			c->Render(window, screenWidth, screenHeight);
			// Checks for collisions with player
			if (c->GetScreenPos() == playerSnake->GetScreenPos())
			{
				c->PickedUp();
				playerSnake->GrowTail();
			}

			// CHecks for collisions with ai
			if (c->GetScreenPos() == aiSnake->GetScreenPos())
			{
				c->PickedUp();
				aiSnake->GrowTail();
			}

			// Keeps collectables in playing field
			if (c->GetScreenPos().y < water->GetScreenPos().y - 20.0f)
			{
				c->Floating();
			}

			// AI COLLECTABLE CHECKS
			// Collectable south
			if ((aiSnake->GetScreenPos().y - 20.0f == c->GetScreenPos().y) && (aiSnake->GetScreenPos().x == c->GetScreenPos().x))
			{
				aiSnake->CollectableSouth();
			}
			// Collectable north
			if ((aiSnake->GetScreenPos().y + 20.0f == c->GetScreenPos().y) && (aiSnake->GetScreenPos().x == c->GetScreenPos().x))
			{
				aiSnake->CollectableNorth();
			}
			// Collectable east
			if ((aiSnake->GetScreenPos().x - 20.0f == c->GetScreenPos().y) && (aiSnake->GetScreenPos().y == c->GetScreenPos().y))
			{
				aiSnake->CollectableEast();
			}
			// Collectable west
			if ((aiSnake->GetScreenPos().x + 20.0f == c->GetScreenPos().y) && (aiSnake->GetScreenPos().y == c->GetScreenPos().y))
			{
				aiSnake->CollectableWest();
			}
		}

		// Checks if player is above water or not
		if (playerSnake->GetScreenPos().y < water->GetScreenPos().y)
		{
			playerSnake->AboveWater(screenWidth);
		}
		else
		{
			playerSnake->BelowWater();
		}

		// Checks if ai is above water or not
		if (aiSnake->GetScreenPos().y < water->GetScreenPos().y)
		{
			aiSnake->AboveWater(screenWidth);
		}
		else
		{
			aiSnake->BelowWater();
		}

		// Checks if player is more than one above water level
		if (playerSnake->GetScreenPos().y < water->GetScreenPos().y - 20.0f)
		{
			playerSnake->Floating();
		}

		// Checks if ai is more than one above water level
		if (aiSnake->GetScreenPos().y < water->GetScreenPos().y - 20.0f)
		{
			aiSnake->Floating();
		}

		// Lowers water level
		if (waterLeak >= 20)
		{
			water->Leak();
			waterLeak = 0;
		}
		waterLeak++;

		window.display();
		window.clear();
	}

	delete playerSnake;
	delete aiSnake;
	delete water;
	for (Collectable *c : collectableItems)
	{
		delete c;
	}
}