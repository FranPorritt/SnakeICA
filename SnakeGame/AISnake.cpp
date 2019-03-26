#include "AISnake.h"
#include <iostream>

AISnake::AISnake(sf::Vector2f screenPosArg, sf::Color colorArg, float radiusArg) :
	Snake(screenPosArg, colorArg, radiusArg)
{
}

AISnake::~AISnake()
{
}

void AISnake::Move()
{
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

void AISnake::Update(int &screenWidth, int &screenHeight, sf::RenderWindow & window, sf::Vector2f &waterScreenPos)
{
	//Checks if snake collides with window edges
	if (screenPos.x < 0 || screenPos.x > screenWidth - radius * 2)
	{
		isDead = true;
	}
	if (screenPos.y < 0 || screenPos.y > screenHeight - radius * 2)
	{
		isDead = true;
	}

	// Edge checks
	if (screenPos.x == 0) // West edge
	{
		if (direction == EDirection::eWest) //Heading towards edge
		{
			if (rand() % edgeChance != 0)
			{
				if ((rand() % 2 == 0) && (!isAboveWater))
				{
					direction = EDirection::eNorth;
				}
				else
				{
					direction = EDirection::eSouth;
				}
			}
		}
	}

	if (screenPos.x == screenWidth - radius * 2) // East edge
	{
		if (direction == EDirection::eEast) //Heading towards edge
		{
			if (rand() % edgeChance != 0)
			{
				if ((rand() % 2 == 0) && (!isAboveWater))
				{
					direction = EDirection::eNorth;
				}
				else
				{
					direction = EDirection::eSouth;
				}
			}
		}
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
		direction = EDirection::eNorth;

		if (movementSteps >= drowningSteps)
		{
			SegmentList.pop_back();
			movementSteps = 0;
		}
	}

	if (SegmentList.size() == 0) // Checks if snake is alive
	{
		isDead = true;
	}

	if (isDead)
	{
		Dead(window);
	}

	movementSteps++;
	//DisplayAir(window);
}

void AISnake::AboveWater(int &screenWidth)
{
	isAboveWater = true;
	isDrowning = false;

	// Sets direction of snake once above water
	if (!isDirectionSet)
	{
		if ((screenPos.x >= screenWidth / 2) && (direction != EDirection::eEast))
		{
			direction = EDirection::eWest;
		}
		else if ((screenPos.x <= screenWidth / 2) && (direction != EDirection::eWest))
		{
			direction = EDirection::eEast;
		}
	}
	// Sets direction above water only once so ai is free to move to collectables
	isDirectionSet = true;
}

void AISnake::BelowWater()
{
	isAboveWater = false;
	isDirectionSet = false;
}

void AISnake::CollectableNorth()
{
	if (direction != EDirection::eSouth)
	{
		direction = EDirection::eNorth;
	}
}

void AISnake::CollectableSouth()
{
	if (direction != EDirection::eNorth)
	{
		direction = EDirection::eSouth;
	}
}

void AISnake::CollectableEast()
{
	if (direction != EDirection::eWest)
	{
		direction = EDirection::eEast;
	}
}

void AISnake::CollectableWest()
{
	if (direction != EDirection::eEast)
	{
		direction = EDirection::eWest;
	}
}

sf::Vector2f AISnake::SetRandomDestination()
{
	float x = rand() % 1000;
	float y = rand() % 750;

	sf::Vector2f randomDestination = { x,y };

	return randomDestination;
}

void AISnake::Dead(sf::RenderWindow & window)
{
	SegmentList.clear();
}
