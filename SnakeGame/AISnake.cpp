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
	//score = SegmentList.size();

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

	/*if (isDead)
	{
		Dead(window, score);
	}*/

	movementSteps++;
	//DisplayAir(window);
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

void AISnake::Dead(sf::RenderWindow & window, int &score)
{
	SegmentList.clear();
}
