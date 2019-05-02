#include "Game.h"
#include "Snake.h"
#include "Water.h"
#include "AISnake.h"
#include "MenuSnake.h"
#include "Pause.h"
#include "UI.h"
#include <iostream>

Game::Game()
{
}

Game::~Game()
{
}

void Game::Update(sf::RenderWindow& window, const int& screenWidth, const int& screenHeight, sf::Vector2f& waterScreenPos)
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

void Game::PlayerSelectScreen(sf::RenderWindow& window, const int& screenWidth, const int& screenHeight, sf::Vector2f& waterScreenPos)
{
	sf::Clock clock;
	sf::Font font;
	if (!font.loadFromFile("ka1.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	UI* ui = new UI();

	sf::Vector2f playerSnakePos = { 440, 440 };
	for (int snakeIndex = 0; snakeIndex < 7; snakeIndex++)
	{
		playerSnakeBody.push_back(new MenuSnake(playerSnakePos, sf::Color::Green, 10.0f));
		playerSnakePos.x += 20.0f;
	}

	sf::Vector2f AI1SnakePos = { 440, 490 };
	for (int snakeIndex = 0; snakeIndex < 7; snakeIndex++)
	{
		AI1SnakeBody.push_back(new MenuSnake(AI1SnakePos, sf::Color::Yellow, 10.0f));
		AI1SnakePos.x += 20.0f;
	}

	sf::Vector2f AI2SnakePos = { 440, 540 };
	for (int snakeIndex = 0; snakeIndex < 7; snakeIndex++)
	{
		AI2SnakeBody.push_back(new MenuSnake(AI2SnakePos, sf::Color::Magenta, 10.0f));
		AI2SnakePos.x += 20.0f;
	}

	sf::Vector2f AI3SnakePos = { 440, 590 };
	for (int snakeIndex = 0; snakeIndex < 7; snakeIndex++)
	{
		AI3SnakeBody.push_back(new MenuSnake(AI3SnakePos, sf::Color::Cyan, 10.0f));
		AI3SnakePos.x += 20.0f;
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
		ui->Menu(window, screenWidth, screenHeight);

		sf::RectangleShape singleSelect({ 180.0f, 5.0f });
		singleSelect.setPosition(screenWidth / 4, 400);
		singleSelect.setFillColor(sf::Color::Red);
		singleSelect.setOrigin(floor(singleSelect.getLocalBounds().width / 2), floor(singleSelect.getLocalBounds().height / 2));


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

		switch (currentSelection)
		{
		case 0:
			window.draw(singleSelect);

			for (MenuSnake* ssb : playerSnakeBody)
			{
				ssb->Render(window);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				currentState = gameState::singlePlayer;
			}
			break;

		case 1:
			window.draw(oneSelect);

			for (MenuSnake* osb : playerSnakeBody)
			{
				osb->Render(window);
			}

			for (MenuSnake* ai1 : AI1SnakeBody)
			{
				ai1->Render(window);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				aiPlayers = 1;
				currentState = gameState::aiPlayer;
			}
			break;

		case 2:
			window.draw(twoSelect);

			for (MenuSnake* osb : playerSnakeBody)
			{
				osb->Render(window);
			}

			for (MenuSnake* ai1 : AI1SnakeBody)
			{
				ai1->Render(window);
			}

			for (MenuSnake* ai2 : AI2SnakeBody)
			{
				ai2->Render(window);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				aiPlayers = 2;
				currentState = gameState::aiPlayer;
			}
			break;

		case 3:
			window.draw(threeSelect);

			for (MenuSnake* osb : playerSnakeBody)
			{
				osb->Render(window);
			}

			for (MenuSnake* ai1 : AI1SnakeBody)
			{
				ai1->Render(window);
			}

			for (MenuSnake* ai2 : AI2SnakeBody)
			{
				ai2->Render(window);
			}

			for (MenuSnake* ai3 : AI3SnakeBody)
			{
				ai3->Render(window);
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			window.close();
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

	UI* ui = new UI();

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

		ui->GameOver(window);
		ui->GameEnd(window, playerSnakeScore);
		ui->HighScore(window, playerSnakeScore);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			currentState = gameState::restart;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			window.close();
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

	UI* ui = new UI();

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

		ui->GameEnd(window, playerSnakeScore);
		ui->GameWon(window);
		ui->HighScore(window, playerSnakeScore);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			currentState = gameState::restart;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			window.close();
		}

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

void Game::Run(sf::RenderWindow& window, const int& screenWidth, const int& screenHeight, sf::Vector2f& waterScreenPos)
{
	sf::Clock clock;
	srand(time(0));

	Water* water = new Water(sf::Color::Blue, { (float)screenWidth, (float)screenHeight - 20.0f });
	Snake * playerSnake = new Snake({ 500,740 }, sf::Color::Green, 10.0f);
	Pause * pause = new Pause();

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			isPaused = !isPaused;
		}

		water->Render(window);
		for (Collectable* c : collectableItems)
		{
			c->Render(window, screenWidth, screenHeight);
		}
		playerSnake->Render(window);

		if (!isPaused)
		{
			playerSnake->Move();
			playerSnake->Update(screenWidth, screenHeight, window, waterScreenPos);


			for (Collectable* c : collectableItems)
			{
				// Checks for collisions with player
				if (c->GetScreenPos() == playerSnake->GetScreenPos())
				{
					if (c->GetWhiteBonus())
					{
						playerSnake->GrowWhiteBonusTail();
					}
					else if (c->GetPurpleBonus())
					{
						playerSnake->GrowPurpleBonusTail();
					}
					else
					{
						playerSnake->GrowTail();
					}
					c->PickedUp(*water, screenHeight);
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

			if (water->GetScreenPos().y > screenHeight)
			{
				playerSnakeScore = playerSnake->GetScore();
				currentState = gameState::gameOver;
			}

			if (playerSnake->DeadCheck())
			{
				playerSnakeScore = playerSnake->GetScore();
				currentState = gameState::gameOver;
			}
		}
		else
		{
			// Paused
			pause->Render(window);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) // Quit - Return to Menu
			{
				currentState = gameState::restart;
			}
		}

		window.display();
		window.clear();
	}

	delete playerSnake;
	delete water;
	for (Collectable* c : collectableItems)
	{
		delete c;
	}
}

void Game::AIRun(sf::RenderWindow & window, const int& screenWidth, const int& screenHeight, sf::Vector2f & waterScreenPos)
{
	sf::Clock clock;
	srand(time(0));

	Water* water = new Water(sf::Color::Blue, { (float)screenWidth, (float)screenHeight - 20.0f });
	Snake * playerSnake = new Snake({ 500,760 }, sf::Color::Green, 10.0f);
	Pause * pause = new Pause();

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			isPaused = !isPaused;
		}

		water->Render(window);
		playerSnake->Render(window);
		for (Collectable* c : collectableItems)
		{
			c->Render(window, screenWidth, screenHeight);
		}
		for (AISnake* ai : aiSnakes)
		{
			ai->Render(window);
		}

		if (!isPaused)
		{
			playerSnake->Move();
			playerSnake->Update(screenWidth, screenHeight, window, waterScreenPos);

			for (AISnake* ai : aiSnakes)
			{
				if (!ai->DeadCheck())
				{
					ai->Move();
					ai->Update(screenWidth, screenHeight, window, waterScreenPos, collectableItems);
					ai->Pathfinding(collectableItems); // Determines which collectable is closest
				}
			}

			for (Collectable* c : collectableItems)
			{
				// Keeps collectables in playing field
				if (c->GetScreenPos().y < water->GetScreenPos().y - 20.0f)
				{
					c->Floating();
				}

				// Checks for collisions with player
				if (c->GetScreenPos() == playerSnake->GetScreenPos())
				{
					if (c->GetWhiteBonus())
					{
						playerSnake->GrowWhiteBonusTail();
					}
					else if (c->GetPurpleBonus())
					{
						playerSnake->GrowPurpleBonusTail();
					}
					else
					{
						playerSnake->GrowTail();
					}
					c->PickedUp(*water, screenHeight);
				}

				// AI COLLECTABLE CHECKS
				for (AISnake* ai : aiSnakes)
				{
					// Checks for collisions with ai
					if (c->GetScreenPos() == ai->GetScreenPos())
					{
						if (c->GetWhiteBonus())
						{
							ai->GrowWhiteBonusTail();
						}
						else if (c->GetPurpleBonus())
						{
							ai->GrowPurpleBonusTail();
						}
						else
						{
							ai->GrowTail();
						}
						c->PickedUp(*water, screenHeight);
						std::cout << "AI PICKED UP" << std::endl;
					}
				}
			}

			// Snake Vs Snake Collisions
			for (AISnake* ai : aiSnakes)
			{
				if (!ai->DeadCheck())
				{
					aiHeadPos = ai->GetHeadPos();
					playerHeadPos = playerSnake->GetHeadPos();

					//Player VS AI, player collides with ai
					if (ai->PlayerCollision(playerHeadPos))
					{
						playerSnakeScore = playerSnake->GetScore();
						currentState = gameState::gameOver;
					}

					// AI VS PLAYER, ai collides with player
					if (playerSnake->AICollision(aiHeadPos))
					{
						std::cout << "AI COLLISION WITH PLAYER" << std::endl;
						ai->Dead();
						playerSnake->ResetCollision();
						break;
					}

					// AI VS AI, ai collides with ai
					for (AISnake* secondAI : aiSnakes) // Compares to second snake
					{
						if (!secondAI->DeadCheck())
						{
							if (secondAI != ai) // Stops it from comparing to itself
							{
								aiHeadPos = secondAI->GetHeadPos();

								if (ai->AICollision(aiHeadPos))
								{
									std::cout << "AI COLLISION" << std::endl;
									secondAI->Dead();  
									break;
								}
							}
						}
					}
				}
			}

			// AI Pathfinding
			for (AISnake* ai : aiSnakes)
			{
				for (Collectable* c : collectableItems)
				{
					// Gets distance between AI and collectable			
					xDistance = ai->GetScreenPos().x - c->GetScreenPos().x;
					if (xDistance < 0)
					{
						xDistance = -xDistance;
					}
					yDistance = ai->GetScreenPos().y - c->GetScreenPos().y;
					if (yDistance < 0)
					{
						yDistance = -yDistance;
					}
					distance = xDistance * 2 + yDistance * 2;
					ai->CollectableDistance(distance);
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
			for (AISnake* ai : aiSnakes)
			{
				if (ai->GetScreenPos().y < water->GetScreenPos().y)
				{
					ai->AboveWater(screenWidth);
				}
				else
				{
					ai->BelowWater();
				}

				// Checks if ai is more than one above water level
				if (ai->GetScreenPos().y < water->GetScreenPos().y - 20.0f)
				{
					ai->Floating();
				}
			}

			int airIndex = 0;
			for (AISnake* ai : aiSnakes)
			{
				if (!ai->DeadCheck())
				{
					if (!ai->GetDrowning())
					{
						airLeft = 100 - ai->GetMovementSteps();
						DisplayAIAir(window, airPos[airIndex], color[airIndex]);
					}
				}
				airIndex++;
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

			if (water->GetScreenPos().y >= screenHeight)
			{
				currentState = gameState::gameOver;
			}
		}
		else  //isPaused
		{
			// Paused
			pause->Render(window);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) // Quit - Return to Menu
			{
				currentState = gameState::restart;
			}
		}

		window.display();
		window.clear();

		// End game checks
		allAIDead = true;
		for (AISnake* ai : aiSnakes)
		{
			if (!ai->DeadCheck())
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
	for (AISnake* ai : aiSnakes)
	{
		delete ai;
	}
	delete water;
	for (Collectable* c : collectableItems)
	{
		delete c;
	}
}

void Game::DisplayAIAir(sf::RenderWindow & window, sf::Vector2f & airPos, sf::Color & color)
{
	sf::Font font;
	if (!font.loadFromFile("ka1.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	sf::RectangleShape airBackground;
	airBackground.setSize({ 100,20 });
	airBackground.setFillColor(sf::Color::White);
	airBackground.setPosition(airPos);

	sf::RectangleShape airRemaining;
	airRemaining.setSize({ airLeft, 20 });
	airRemaining.setFillColor(color);
	airRemaining.setPosition(airPos);

	window.draw(airBackground);
	window.draw(airRemaining);
}

gameState Game::GetState()
{
	return currentState;
}

bool Game::GetRestart()
{
	return isRestarting;
}