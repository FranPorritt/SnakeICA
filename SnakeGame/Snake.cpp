#include "Snake.h"
#include "Game.h"
#include <iostream>
#include <time.h>

#include "Water.h"

Snake::Snake(sf::Vector2f screenPosArg, sf::Color colorArg, float radiusArg) :
	screenPos(screenPosArg), color(colorArg), radius(radiusArg)
{
	SegmentList.push_front(screenPos);
}

Snake::~Snake()
{
}

void Snake::Render(sf::RenderWindow & window)
{
	for (auto &i : SegmentList)
	{
		sf::CircleShape shape(radius);
		shape.setPosition(i);
		shape.setFillColor(color);
		window.draw(shape);
	}
}

void Snake::Move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction = EDirection::eNorth;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction = EDirection::eSouth;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction = EDirection::eWest;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction = EDirection::eEast;
	}
	else if (isDead)
	{
		direction = EDirection::eStop;
	}

	switch (direction)
	{
	case EDirection::eNorth:
		screenPos.y -= radius * 2;
		break;

	case EDirection::eSouth:
		screenPos.y += radius * 2;
		break;

	case EDirection::eEast:
		screenPos.x += radius * 2;
		break;

	case EDirection::eWest:
		screenPos.x -= radius * 2;
		break;

	case EDirection::eStop:
		break;

	default:
		break;
	}

	// Adds segment to front and removes one to back to simulate movement
	SegmentList.push_front(screenPos);
	SegmentList.pop_back();
}


void Snake::Update(int &screenWidth, int &screenHeight, sf::RenderWindow & window, sf::Vector2f &waterScreenPos)
{
	score = SegmentList.size() - 1;

	//Checks if snake collides with window edges
	if (screenPos.x < 0 || screenPos.x > screenWidth - radius * 2)
	{
		isDead = true;
	}
	if (screenPos.y < 0 || screenPos.y > screenHeight - radius * 2)
	{
		isDead = true;
	}

	// Self Collision Check
	int index = 0;
	for (auto &segment : SegmentList)
	{
		// Skips the first element so the head isn't being compared to the head, only the body.
		if (++index > 1)
		{
			// Checks head doesn't collide with body.
			if (SegmentList.front() == segment)
			{
				isDead = true;
			}
		}
	}

	// Air checks
	if (isAboveWater)
	{
		movementSteps = 0;
	}

	if ((!isAboveWater) && (movementSteps >= breathSteps)) // Checks if snake is drowning
	{
		isDrowning = true;
	}

	if (isDrowning) // Removes a tail segment until surface is reached
	{
		if (movementSteps >= drowningSteps)
		{
			SegmentList.pop_back();
			movementSteps = 0;
		}
		DrowningText(window);
	}

	if (SegmentList.size() == 0) // Checks if snake is alive
	{
		isDead = true;
	}

	movementSteps++;
	DisplayAir(window);
	DisplayScore(window);
}

void Snake::AboveWater(int &screenWidth)
{
	isAboveWater = true;
	isDrowning = false;

	// Sets direction of snake once above water
	if ((screenPos.x >= screenWidth / 2) && (direction != EDirection::eEast))
	{
		direction = EDirection::eWest;
	}
	else if ((screenPos.x <= screenWidth / 2) && (direction != EDirection::eWest))
	{
		direction = EDirection::eEast;
	}
}

void Snake::BelowWater()
{
	isAboveWater = false;
}

void Snake::Floating()
{
	screenPos.y += radius * 2;
}

void Snake::GrowTail()
{
	SegmentList.push_front(screenPos);
}

bool Snake::DeadCheck()
{
	return isDead;
}

sf::Vector2f Snake::GetScreenPos()
{
	return screenPos;
}

int Snake::GetScore()
{
	return score;
}

// SFML Rendering

void Snake::DisplayAir(sf::RenderWindow & window)
{
	float airLeft = (100 - movementSteps) * 2;

	sf::Font font;
	if (!font.loadFromFile("ka1.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	sf::Text airText;
	airText.setFont(font);
	airText.setCharacterSize(20);
	airText.setPosition(35, 15);
	airText.setString("AIR: ");
	airText.setFillColor(sf::Color::Red);

	airText.setOrigin(floor(airText.getLocalBounds().width / 2), floor(airText.getLocalBounds().height / 2));

	sf::RectangleShape airBackground;
	airBackground.setSize({ 200,20 });
	airBackground.setFillColor(sf::Color::White);
	airBackground.setPosition({ 60,10 });

	sf::RectangleShape airRemaining;
	airRemaining.setSize({ airLeft, 20 });
	airRemaining.setFillColor(sf::Color::Green);
	airRemaining.setPosition({ 60,10 });
	
	window.draw(airText);
	window.draw(airBackground);

	if (!isDrowning)
	{
		window.draw(airRemaining);
	}
}

void Snake::DisplayScore(sf::RenderWindow & window)
{
	sf::Font font;
	if (!font.loadFromFile("ka1.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setPosition(900, 15);
	scoreText.setString("SCORE: " + std::to_string(score));
	scoreText.setFillColor(sf::Color::Red);

	scoreText.setOrigin(floor(scoreText.getLocalBounds().width / 2), floor(scoreText.getLocalBounds().height / 2));

	window.draw(scoreText);
}

void Snake::DrowningText(sf::RenderWindow & window)
{
	sf::Font font;
	if (!font.loadFromFile("ka1.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	sf::Text drowningText;
	drowningText.setFont(font);
	drowningText.setCharacterSize(50);
	drowningText.setPosition(350, 600);
	drowningText.setString("DROWNING!");
	drowningText.setFillColor(sf::Color::White);

	window.draw(drowningText);
}