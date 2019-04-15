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

		sf::Text startText;
		startText.setFont(font);
		startText.setCharacterSize(25);
		startText.setPosition(500, 650);
		startText.setString("PRESS SPACE TO START");
		startText.setFillColor(sf::Color::Red);
		startText.setOrigin(floor(startText.getLocalBounds().width / 2), floor(startText.getLocalBounds().height / 2));

		sf::Text quitText;
		quitText.setFont(font);
		quitText.setCharacterSize(25);
		quitText.setPosition(500, 700);
		quitText.setString("PRESS Q TO QUIT");
		quitText.setFillColor(sf::Color::Red);
		quitText.setOrigin(floor(quitText.getLocalBounds().width / 2), floor(quitText.getLocalBounds().height / 2));

		window.draw(titleText);
		window.draw(singleText);
		window.draw(aiText);
		window.draw(startText);
		window.draw(quitText);

		switch (currentSelection)
		{
		case 0:
			window.draw(singleSelect);

			for (MenuSnake *ssb : playerSnakeBody)
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

			for (MenuSnake *osb : playerSnakeBody)
			{
				osb->Render(window);
			}

			for (MenuSnake *ai1 : AI1SnakeBody)
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

			for (MenuSnake *osb : playerSnakeBody)
			{
				osb->Render(window);
			}

			for (MenuSnake *ai1 : AI1SnakeBody)
			{
				ai1->Render(window);
			}

			for (MenuSnake *ai2 : AI2SnakeBody)
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

			for (MenuSnake *osb : playerSnakeBody)
			{
				osb->Render(window);
			}

			for (MenuSnake *ai1 : AI1SnakeBody)
			{
				ai1->Render(window);
			}

			for (MenuSnake *ai2 : AI2SnakeBody)
			{
				ai2->Render(window);
			}

			for (MenuSnake *ai3 : AI3SnakeBody)
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
		gameOverText.setCharacterSize(85);
		gameOverText.setPosition(500, 100);
		gameOverText.setString("GAME OVER");
		gameOverText.setFillColor(sf::Color::Red);
		gameOverText.setOrigin(floor(gameOverText.getLocalBounds().width / 2), floor(gameOverText.getLocalBounds().height / 2));

		sf::Text scoreText;
		scoreText.setFont(font);
		scoreText.setCharacterSize(50);
		scoreText.setPosition(500, 250);
		scoreText.setString("SCORE: " + std::to_string(playerSnakeScore));
		scoreText.setFillColor(sf::Color::Red);
		scoreText.setOrigin(floor(scoreText.getLocalBounds().width / 2), floor(scoreText.getLocalBounds().height / 2));

		sf::Text restartText;
		restartText.setFont(font);
		restartText.setCharacterSize(35);
		restartText.setPosition(500, 600);
		restartText.setString("PRESS SPACE TO RESTART");
		restartText.setFillColor(sf::Color::Red);
		restartText.setOrigin(floor(restartText.getLocalBounds().width / 2), floor(restartText.getLocalBounds().height / 2));

		sf::Text quitText;
		quitText.setFont(font);
		quitText.setCharacterSize(35);
		quitText.setPosition(500, 700);
		quitText.setString("PRESS Q TO QUIT");
		quitText.setFillColor(sf::Color::Red);
		quitText.setOrigin(floor(quitText.getLocalBounds().width / 2), floor(quitText.getLocalBounds().height / 2));

		window.draw(gameOverText);
		window.draw(scoreText);
		window.draw(restartText);
		window.draw(quitText);

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

		sf::Text highScoreText;
		highScoreText.setFont(font);
		highScoreText.setCharacterSize(50);
		highScoreText.setPosition(500, 350);
		highScoreText.setString("HIGH SCORE: " + std::to_string(highScore));
		highScoreText.setFillColor(sf::Color::Red);
		highScoreText.setOrigin(floor(highScoreText.getLocalBounds().width / 2), floor(highScoreText.getLocalBounds().height / 2));

		window.draw(highScoreText);

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
		gameWonText.setCharacterSize(85);
		gameWonText.setPosition(500, 100);
		gameWonText.setString("GAME WON");
		gameWonText.setFillColor(sf::Color::Red);
		gameWonText.setOrigin(floor(gameWonText.getLocalBounds().width / 2), floor(gameWonText.getLocalBounds().height / 2));

		sf::Text scoreText;
		scoreText.setFont(font);
		scoreText.setCharacterSize(50);
		scoreText.setPosition(500, 250);
		scoreText.setString("SCORE: " + std::to_string(playerSnakeScore));
		scoreText.setFillColor(sf::Color::Red);
		scoreText.setOrigin(floor(scoreText.getLocalBounds().width / 2), floor(scoreText.getLocalBounds().height / 2));

		sf::Text restartText;
		restartText.setFont(font);
		restartText.setCharacterSize(35);
		restartText.setPosition(500, 600);
		restartText.setString("PRESS SPACE TO RESTART");
		restartText.setFillColor(sf::Color::Red);
		restartText.setOrigin(floor(restartText.getLocalBounds().width / 2), floor(restartText.getLocalBounds().height / 2));

		sf::Text quitText;
		quitText.setFont(font);
		quitText.setCharacterSize(35);
		quitText.setPosition(500, 700);
		quitText.setString("PRESS Q TO QUIT");
		quitText.setFillColor(sf::Color::Red);
		quitText.setOrigin(floor(quitText.getLocalBounds().width / 2), floor(quitText.getLocalBounds().height / 2));

		window.draw(gameWonText);
		window.draw(scoreText);
		window.draw(restartText);
		window.draw(quitText);

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
		
		sf::Text highScoreText;
		highScoreText.setFont(font);
		highScoreText.setCharacterSize(50);
		highScoreText.setPosition(500, 350);
		highScoreText.setString("HIGH SCORE: " + std::to_string(highScore));
		highScoreText.setFillColor(sf::Color::Red);
		highScoreText.setOrigin(floor(highScoreText.getLocalBounds().width / 2), floor(highScoreText.getLocalBounds().height / 2));

		window.draw(highScoreText);

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

void Game::Run(sf::RenderWindow& window, const int &screenWidth, const int &screenHeight, sf::Vector2f &waterScreenPos)
{
	sf::Clock clock;
	srand(time(0));

	Water* water = new Water(sf::Color::Blue, { (float)screenWidth, (float)screenHeight - 20.0f });
	Snake* playerSnake = new Snake({ 500,740 }, sf::Color::Green, 10.0f);

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
	Snake* playerSnake = new Snake({ 500,760 }, sf::Color::Green, 10.0f);

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
			for (AISnake *s : aiSnakes)
			{
				// Checks for collisions with ai
				if (c->GetScreenPos() == s->GetScreenPos())
				{
					if (c->GetWhiteBonus())
					{
						s->GrowWhiteBonusTail();
					}
					else if (c->GetPurpleBonus())
					{
						s->GrowPurpleBonusTail();
					}
					else
					{
						s->GrowTail();
					}
					c->PickedUp(*water, screenHeight);
					std::cout << "AI PICKED UP" << std::endl;
				}
			}
		}

		// Snake Vs Snake Collisions
		for (AISnake *s : aiSnakes)
		{
			if (!s->DeadCheck())
			{
				aiHeadPos = s->GetHeadPos();
				playerHeadPos = playerSnake->GetHeadPos();

				//Player VS AI, player collides with ai
				if (s->PlayerCollision(playerHeadPos))
				{
					playerSnakeScore = playerSnake->GetScore();
					currentState = gameState::gameOver;
				}

				// AI VS PLAYER, ai collides with player
				if (playerSnake->AICollision(aiHeadPos))
				{
					std::cout << "AI COLLISION WITH PLAYER" << std::endl;
					s->Dead();
					//delete s;
					playerSnake->ResetCollision();
					break;
				}

				// AI VS AI, ai collides with ai
				for (AISnake *ss : aiSnakes) // Compares to second snake
				{
					if (!ss->DeadCheck())
					{
						if (ss != s) // Stops it from comparing to itself
						{
							aiHeadPos = ss->GetHeadPos();

							if (s->AICollision(aiHeadPos))
							{
								std::cout << "AI COLLISION" << std::endl;
								ss->Dead();  // CAUSES DEBUG ASSERTION FAILURE
								//delete ss;
								break;
							}
						}
					}
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

		int airIndex = 0;
		for (AISnake *snake : aiSnakes)
		{
			if (!snake->DeadCheck())
			{
				if (!snake->GetDrowning())
				{
					airLeft = 100 - snake->GetMovementSteps();
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

void Game::DisplayAIAir(sf::RenderWindow& window, sf::Vector2f &airPos, sf::Color &color)
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