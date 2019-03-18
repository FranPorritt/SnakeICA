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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			AIRun(window, screenWidth, screenHeight, waterScreenPos);
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

	// Creates collectables
	for (int collectableIndex = 0; collectableIndex < maxActiveCollectables; collectableIndex++)
	{
		// Finds random screen position
		float x = (rand() % 50 + 1) * 20;
		float y = (rand() % 36 + 1) * 20;

		// Checks collectable doesn't spawn above water
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
	    playerSnake->Update(screenWidth, screenHeight, window, waterScreenPos);
		playerSnake->Render(window);

		for (Collectable *c : collectableItems)
		{
			c->Render(window, screenWidth, screenHeight);
			// Checks for collisions with player
			if (c->GetScreenPos() == playerSnake->GetScreenPos())
			{
				c->PickedUp();
				playerSnake->GrowTail();
			}

			// Keeps collectables in playing field
			if (c->GetScreenPos().y < water->GetScreenPos().y - 20.0f)
			{
				c->Floating();
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

		// Checks if player is more than one above water level
		if (playerSnake->GetScreenPos().y < water->GetScreenPos().y - 20.0f)
		{
			playerSnake->Floating();
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
	delete water;
	for (Collectable *c : collectableItems)
	{
		delete c;
	}
}

void Game::AIRun(sf::RenderWindow& window, int &screenWidth, int &screenHeight, sf::Vector2f &waterScreenPos)
{
	sf::Clock clock;
	srand(time(0));

	Water* water = new Water(sf::Color::Blue, { (float)screenWidth, (float)screenHeight - 20.0f });
	Snake* playerSnake = new Snake({ 500,500 }, sf::Color::Green, 10.0f);
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

		AICollectableDistance.clear();

		for (Collectable *c : collectableItems)
		{
			c->Render(window, screenWidth, screenHeight);

			// Checks for collisions with player
			if (c->GetScreenPos() == playerSnake->GetScreenPos())
			{
				c->PickedUp();
				playerSnake->GrowTail();
			}

			// Checks for collisions with ai
			if (c->GetScreenPos() == aiSnake->GetScreenPos())
			{
				c->PickedUp();
				aiSnake->GrowTail();
				std::cout << "PICKED UP" << std::endl;
			}

			// Keeps collectables in playing field
			if (c->GetScreenPos().y < water->GetScreenPos().y - 20.0f)
			{
				c->Floating();
			}

			// AI COLLECTABLE CHECKS
			// Gets distance between AI and collectable
			xDistance = aiSnake->GetScreenPos().x - c->GetScreenPos().x;
			if (xDistance < 0)
			{
				xDistance = -xDistance;
			}
			yDistance = aiSnake->GetScreenPos().y - c->GetScreenPos().y;
			if (yDistance < 0)
			{
				yDistance = -yDistance;
			}
			distance = xDistance * 2 + yDistance * 2;
			AICollectableDistance.push_back(distance);
		}

		// Determines which collectable is closest
		closestValue = AICollectableDistance[0];
		for (int distanceIndex = 0; distanceIndex < AICollectableDistance.size(); distanceIndex++)
		{
			if (AICollectableDistance[distanceIndex] < closestValue)
			{
				thirdClosestValue = secondClosestValue;
				thirdClosestValuePos = secondClosestValuePos;
				secondClosestValue = closestValue;
				secondClosestValuePos = closestValuePos;
				closestValue = AICollectableDistance[distanceIndex];
				closestValuePos = distanceIndex;
			}
		}

		if (collectableItems[closestValuePos]->Alive())
		{
			AITargetCollectable = collectableItems[closestValuePos]->GetScreenPos();
		}
		else
		{
			if (collectableItems[secondClosestValuePos]->Alive())
			{
				AITargetCollectable = collectableItems[secondClosestValuePos]->GetScreenPos();
			}
			else
			{
				AITargetCollectable = collectableItems[thirdClosestValuePos]->GetScreenPos();
			}
		}
		xTargetDistance = aiSnake->GetScreenPos().x - AITargetCollectable.x;
		if (xTargetDistance < 0)
		{
			xTargetDistance = -xTargetDistance;
		}
		yDistance = aiSnake->GetScreenPos().y - AITargetCollectable.y;
		if (yTargetDistance < 0)
		{
			yTargetDistance = -yTargetDistance;
		}
		
		// Set direction to collectable
		if (xTargetDistance > yTargetDistance)
		{
			if (AITargetCollectable.x > aiSnake->GetScreenPos().x)
			{
				std::cout << "Moving east" << std::endl;
				aiSnake->CollectableEast();
			}
			else
			{
				std::cout << "Moving west" << std::endl;
				aiSnake->CollectableWest();
			}
		}
		else
		{
			if (AITargetCollectable.y > aiSnake->GetScreenPos().y)
			{
				std::cout << "Moving south" << std::endl;
				aiSnake->CollectableSouth();
			}
			else
			{
				std::cout << "Moving north" << std::endl;
				aiSnake->CollectableNorth();
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

		// Checks if player is more than one above water level
		if (playerSnake->GetScreenPos().y < water->GetScreenPos().y - 20.0f)
		{
			playerSnake->Floating();
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