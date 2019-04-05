#include "Game.h"
#include "Snake.h"
#include "Water.h"
#include "AISnake.h"
#include "MenuSnake.h"
#include <iostream>

Game::Game()
{
}

Game::~Game()
{
}

void Game::Update(sf::RenderWindow& window, const int &screenWidth, const int &screenHeight, sf::Vector2f &waterScreenPos)
{
	switch (currentState)
	{
	case gameState::playerSelect:
		PlayerSelectScreen(window, screenWidth, screenHeight, waterScreenPos);
		break;

	case gameState::singlePlayer:
		Run(window, screenWidth, screenHeight, waterScreenPos);
		break;

	case gameState::aiPlayer:
		AIRun(window, screenWidth, screenHeight, waterScreenPos);
		break;

	case gameState::gameOver:
		GameOverScreen(window);
		break;

	case gameState::gameWon:
		GameWonScreen(window);
		break;

	case gameState::restart:
		Restart(window);
		break;

	default:
		break;
	}
}

void Game::PlayerSelectScreen(sf::RenderWindow& window, const int &screenWidth, const int &screenHeight, sf::Vector2f &waterScreenPos)
{
	sf::Clock clock;
	sf::Font font;
	if (!font.loadFromFile("ka1.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	sf::Vector2f singleSnakePos = { 180, 440 };
	for (int snakeIndex = 0; snakeIndex < 7; snakeIndex++)
	{
		singleSnakeBody.push_back(new MenuSnake(singleSnakePos, sf::Color::Green, 10.0f));
		singleSnakePos.x += 20.0f;
	}

	sf::Vector2f optionSnakePos = { 680, 440 };
	for (int snakeIndex = 0; snakeIndex < 7; snakeIndex++)
	{
		optionSnakeBody.push_back(new MenuSnake(optionSnakePos, sf::Color::Green, 10.0f));
		optionSnakePos.x += 20.0f;
	}

	Water* water = new Water(sf::Color::Blue, { (float)screenWidth, (float)screenHeight });
	water->MenuPos();

	while (window.isOpen() && currentState == gameState::playerSelect)
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

		while (clock.getElapsedTime().asMilliseconds() < 100);
		clock.restart();
				
		water->Render(window);
		
		/*for (MenuSnake *ssb : singleSnakeBody)
		{				
			ssb->Wiggle();
		}*/

		sf::Text titleText;
		titleText.setFont(font);
		titleText.setCharacterSize(75);
		titleText.setPosition(screenWidth / 2, screenHeight / 6);
		titleText.setString("SNAKE");
		titleText.setFillColor(sf::Color::Green);
		titleText.setOrigin(floor(titleText.getLocalBounds().width / 2), floor(titleText.getLocalBounds().height / 2));

		sf::Text singleText;
		singleText.setFont(font);
		singleText.setCharacterSize(30);
		singleText.setPosition(screenWidth / 4, 350);
		singleText.setString("SINGLE \n PLAYER");
		singleText.setFillColor(sf::Color::Red);
		singleText.setOrigin(floor(singleText.getLocalBounds().width / 2), floor(singleText.getLocalBounds().height / 2));

		sf::RectangleShape singleSelect({ 180.0f, 5.0f });
		singleSelect.setPosition(screenWidth / 4, 400);
		singleSelect.setFillColor(sf::Color::Red);
		singleSelect.setOrigin(floor(singleSelect.getLocalBounds().width / 2), floor(singleSelect.getLocalBounds().height / 2));

		sf::Text aiText;
		aiText.setFont(font);
		aiText.setCharacterSize(30);
		aiText.setPosition(screenWidth * 0.75, 350);
		aiText.setString("PLAYER \n VS AI \n 1 \t 2 \t 3");
		aiText.setFillColor(sf::Color::Red);
		aiText.setOrigin(floor(aiText.getLocalBounds().width / 2), floor(aiText.getLocalBounds().height / 2));

		sf::RectangleShape oneSelect({ 40.0f, 5.0f });
		oneSelect.setPosition(screenWidth * 0.75 - 70, 420);
		oneSelect.setFillColor(sf::Color::Red);
		oneSelect.setOrigin(floor(oneSelect.getLocalBounds().width / 2), floor(oneSelect.getLocalBounds().height / 2));

		sf::RectangleShape twoSelect({ 40.0f, 5.0f });
		twoSelect.setPosition(screenWidth * 0.75 + 5, 420);
		twoSelect.setFillColor(sf::Color::Red);
		twoSelect.setOrigin(floor(twoSelect.getLocalBounds().width / 2), floor(twoSelect.getLocalBounds().height / 2));

		sf::RectangleShape threeSelect({ 40.0f, 5.0f });
		threeSelect.setPosition(screenWidth * 0.75 + 80, 420);
		threeSelect.setFillColor(sf::Color::Red);
		threeSelect.setOrigin(floor(threeSelect.getLocalBounds().width / 2), floor(threeSelect.getLocalBounds().height / 2));

		window.draw(titleText);
		window.draw(singleText);
		window.draw(aiText);

		switch(currentSelection)
		{
		case 0:
			window.draw(singleSelect);

			for (MenuSnake *ssb : singleSnakeBody)
			{
				ssb->Wiggle();
				ssb->Render(window);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				currentState = gameState::singlePlayer;
			}
			break;

		case 1:
			window.draw(oneSelect);

			for (MenuSnake *osb : optionSnakeBody)
			{
				osb->Render(window);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				aiPlayers = 1;
				currentState = gameState::aiPlayer;
			}
			break;

		case 2:
			window.draw(twoSelect);

			for (MenuSnake *osb : optionSnakeBody)
			{
				osb->Render(window);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				aiPlayers = 2;
				currentState = gameState::aiPlayer;
			}
			break;

		case 3:
			window.draw(threeSelect);

			for (MenuSnake *osb : optionSnakeBody)
			{
				osb->Render(window);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				aiPlayers = 3;
				currentState = gameState::aiPlayer;
			}
			break;

		default:
			break;
		}
		
		wiggleCount++;
		water->MenuLeak();

		// if right button, increase array unless end vice versa, if array num display that line ect
		if (((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) && currentSelection != 0)
		{
			currentSelection--;
		}

		if (((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) && currentSelection != 3)
		{
			currentSelection++;
		}

		window.display();
		window.clear();
	}
}

void Game::GameOverScreen(sf::RenderWindow& window)
{
	sf::Font font;
	if (!font.loadFromFile("ka1.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	while ((window.isOpen()) && (currentState == gameState::gameOver))
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
		gameOverText.setCharacterSize(75);
		gameOverText.setPosition(500, 200);
		gameOverText.setString("GAME OVER");
		gameOverText.setFillColor(sf::Color::Red);

		gameOverText.setOrigin(floor(gameOverText.getLocalBounds().width / 2), floor(gameOverText.getLocalBounds().height / 2));

		sf::Text scoreText;
		scoreText.setFont(font);
		scoreText.setCharacterSize(50);
		scoreText.setPosition(500, 500);
		scoreText.setString("SCORE: " + std::to_string(playerSnakeScore));
		scoreText.setFillColor(sf::Color::Red);

		scoreText.setOrigin(floor(scoreText.getLocalBounds().width / 2), floor(scoreText.getLocalBounds().height / 2));

		window.draw(gameOverText);
		window.draw(scoreText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			currentState = gameState::restart;

			//currentState = gameState::menu;
		}

		window.display();
		window.clear();
	}
}

void Game::GameWonScreen(sf::RenderWindow& window)
{
	sf::Font font;
	if (!font.loadFromFile("ka1.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	while ((window.isOpen()) && (currentState == gameState::gameWon))
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

		sf::Text gameWonText;
		gameWonText.setFont(font);
		gameWonText.setCharacterSize(75);
		gameWonText.setPosition(500, 200);
		gameWonText.setString("GAME WON");
		gameWonText.setFillColor(sf::Color::Red);

		gameWonText.setOrigin(floor(gameWonText.getLocalBounds().width / 2), floor(gameWonText.getLocalBounds().height / 2));

		sf::Text scoreText;
		scoreText.setFont(font);
		scoreText.setCharacterSize(50);
		scoreText.setPosition(500, 500);
		scoreText.setString("SCORE: " + std::to_string(playerSnakeScore));
		scoreText.setFillColor(sf::Color::Red);

		scoreText.setOrigin(floor(scoreText.getLocalBounds().width / 2), floor(scoreText.getLocalBounds().height / 2));

		window.draw(gameWonText);
		window.draw(scoreText);

		window.display();
		window.clear();
	}
}

void Game::Restart(sf::RenderWindow& window)
{
	window.display();
	window.clear();

	isRestarting = true;
}

void Game::Run(sf::RenderWindow& window, const int &screenWidth, const int &screenHeight, sf::Vector2f &waterScreenPos)
{
	sf::Clock clock;
	srand(time(0));

	Water* water = new Water(sf::Color::Blue, { (float)screenWidth, (float)screenHeight - 20.0f });
	Snake* playerSnake = new Snake({ 500,500 }, sf::Color::Green, 10.0f);

	// Creates collectables
	for (int collectableIndex = 0; collectableIndex < maxActiveCollectables; collectableIndex++)
	{
		// Finds random screen position
		float x = (rand() % 50) * 20;
		float y = (rand() % 36) * 20;

		// Checks collectable doesn't spawn above water
		if (y < water->GetScreenPos().y || y >= screenHeight)
		{
			float y = (rand() % 36 + 1) * 20;
		}

		collectableItems.push_back(new Collectable({ x,y }, 10.0f));
	}

	while ((window.isOpen()) && (currentState == gameState::singlePlayer))
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

		while (clock.getElapsedTime().asMilliseconds() < 175);
		clock.restart();

		water->Render(window);

		for (Collectable *c : collectableItems)
		{
			c->Render(window, screenWidth, screenHeight);
		}

		playerSnake->Move();
		playerSnake->Update(screenWidth, screenHeight, window, waterScreenPos);
		playerSnake->Render(window);

		for (Collectable *c : collectableItems)
		{
			// Checks for collisions with player
			if (c->GetScreenPos() == playerSnake->GetScreenPos())
			{
				c->PickedUp(*water, screenHeight);
				if (c->GetBonus())
				{
					playerSnake->GrowBonusTail();
				}
				else
				{
					playerSnake->GrowTail();
				}
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
		if (waterLeak >= 12)
		{
			water->Leak();
			waterLeak = 0;
		}
		waterLeak++;

		if (playerSnake->DeadCheck())
		{
			playerSnakeScore = playerSnake->GetScore();
			currentState = gameState::gameOver;
		}

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

void Game::AIRun(sf::RenderWindow& window, const int &screenWidth, const int &screenHeight, sf::Vector2f &waterScreenPos)
{
	sf::Clock clock;
	srand(time(0));

	Water* water = new Water(sf::Color::Blue, { (float)screenWidth, (float)screenHeight - 20.0f });
	Snake* playerSnake = new Snake({ 500,500 }, sf::Color::Green, 10.0f);

	sf::Color color[3] = { sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan };

	// Creates ai players
	for (int aiSnakesIndex = 0; aiSnakesIndex < aiPlayers; aiSnakesIndex++)
	{
		// Finds random screen position
		float x = (rand() % 50) * 20;
		float y = (rand() % 36) * 20;

		// Checks collectable isn't spawning above water
		if (y < water->GetScreenPos().y || y >= screenHeight)
		{
			float y = (rand() % 36 + 1) * 20;
		}

		aiSnakes.push_back(new AISnake({ x,y }, color[aiSnakesIndex], 10.0f));
	}

	// Creates collectables
	for (int collectableIndex = 0; collectableIndex < maxActiveCollectables; collectableIndex++)
	{
		// Finds random screen position
		float x = (rand() % 50) * 20;
		float y = (rand() % 36) * 20;

		// Checks collectable isn't spawning above water
		if (y < water->GetScreenPos().y || y >= screenHeight)
		{
			float y = (rand() % 36 + 1) * 20;
		}

		collectableItems.push_back(new Collectable({ x,y }, 10.0f));
	}

	while (window.isOpen() && currentState == gameState::aiPlayer)
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

		while (clock.getElapsedTime().asMilliseconds() < 175);
		clock.restart();

		// Snake Vs Snake Collisions
		for (size_t snakeIndex = 0; snakeIndex < aiSnakes.size(); snakeIndex++)
		{
			// Player VS AI
			if (playerSnake->GetHeadPos() == aiSnakes[snakeIndex]->GetScreenPos())
			{
				playerSnakeScore = playerSnake->GetScore();
				currentState = gameState::gameOver;
				break;
			}

			if (!aiSnakes[snakeIndex]->DeadCheck()) // Checks AI is alive
			{
				aiHeadPos = aiSnakes[snakeIndex]->GetHeadPos();

				// AI VS PLAYER
				if (playerSnake->AICollision(aiHeadPos))
				{
					std::cout << "AI COLLISION WITH PLAYER" << std::endl;
					aiSnakes[snakeIndex]->Dead();
					break;
				}


				// TRY USING 'THIS'
				// AI VS AI
				for (size_t secondSnake = snakeIndex + 1; secondSnake < aiSnakes.size(); secondSnake++)
				{
					if (!aiSnakes[secondSnake]->DeadCheck()) // Checks AI is alive
					{
						if (aiSnakes[secondSnake]->AICollision(aiHeadPos))
						{
							std::cout << "AI COLLISION WITH PLAYER" << std::endl;
							aiSnakes[snakeIndex]->Dead();
							break;
						}

						aiHeadPos = aiSnakes[secondSnake]->GetHeadPos();
						if (aiSnakes[snakeIndex]->AICollision(aiHeadPos))
						{
							std::cout << "AI COLLISION WITH PLAYER" << std::endl;
							aiSnakes[secondSnake]->Dead();
							break;
						}
					}
				}
			}
		}

		water->Render(window);

		playerSnake->Move();
		playerSnake->Update(screenWidth, screenHeight, window, waterScreenPos);
		playerSnake->Render(window);

		for (AISnake *s : aiSnakes)
		{
			if (!s->DeadCheck())
			{
				s->Move();
				s->Update(screenWidth, screenHeight, window, waterScreenPos, collectableItems);
				s->Render(window);
				s->Pathfinding(collectableItems); // Determines which collectable is closest
			}
		}

		for (Collectable *c : collectableItems)
		{
			c->Render(window, screenWidth, screenHeight);

			// Keeps collectables in playing field
			if (c->GetScreenPos().y < water->GetScreenPos().y - 20.0f)
			{
				c->Floating();
			}

			// Checks for collisions with player
			if (c->GetScreenPos() == playerSnake->GetScreenPos())
			{
				c->PickedUp(*water, screenHeight);
				if (c->GetBonus())
				{
					playerSnake->GrowBonusTail();
				}
				else
				{
					playerSnake->GrowTail();
				}
			}

			// AI COLLECTABLE CHECKS
			for (AISnake *s : aiSnakes)
			{
				// Checks for collisions with ai
				if (c->GetScreenPos() == s->GetScreenPos())
				{
					c->PickedUp(*water, screenHeight);
					if (c->GetBonus())
					{
						s->GrowBonusTail();
					}
					else
					{
						s->GrowTail();
					}
					std::cout << "AI PICKED UP" << std::endl;
				}
			}
		}

		// AI Pathfinding
		for (AISnake *s : aiSnakes)
		{
			for (Collectable *c : collectableItems)
			{
				// Gets distance between AI and collectable			
				xDistance = s->GetScreenPos().x - c->GetScreenPos().x;
				if (xDistance < 0)
				{
					xDistance = -xDistance;
				}
				yDistance = s->GetScreenPos().y - c->GetScreenPos().y;
				if (yDistance < 0)
				{
					yDistance = -yDistance;
				}
				distance = xDistance * 2 + yDistance * 2;
				s->CollectableDistance(distance);
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
		for (AISnake *s : aiSnakes)
		{
			if (s->GetScreenPos().y < water->GetScreenPos().y)
			{
				s->AboveWater(screenWidth);
			}
			else
			{
				s->BelowWater();
			}

			// Checks if ai is more than one above water level
			if (s->GetScreenPos().y < water->GetScreenPos().y - 20.0f)
			{
				s->Floating();
			}
		}

		// Lowers water level
		if (waterLeak >= 20)
		{
			water->Leak();
			waterLeak = 0;
		}
		waterLeak++;

		if (playerSnake->DeadCheck())
		{
			playerSnakeScore = playerSnake->GetScore();
			currentState = gameState::gameOver;
		}

		window.display();
		window.clear();

		// End game checks
		allAIDead = true;
		for (AISnake *s : aiSnakes)
		{
			if (!s->DeadCheck())
			{
				allAIDead = false;
			}
		}

		if (allAIDead)
		{
			playerSnakeScore = playerSnake->GetScore();
			currentState = gameState::gameWon;
		}
	}

	delete playerSnake;
	for (AISnake *s : aiSnakes)
	{
		delete s;
	}
	delete water;
	for (Collectable *c : collectableItems)
	{
		delete c;
	}
}

gameState Game::GetState()
{
	return currentState;
}

bool Game::GetRestart()
{
	return isRestarting;
}