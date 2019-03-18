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
	srand(time(0));

	// Sets random direction
	if ((rand()%4 == 0) && (direction != EDirection::eSouth))
	{
		direction = EDirection::eNorth;
	}
	else if ((rand() % 4 == 1) && (direction != EDirection::eNorth))
	{
		direction = EDirection::eSouth;
	}
	else if ((rand() % 4 == 2) && (direction != EDirection::eEast))
	{
		direction = EDirection::eWest;
	}
	else if ((rand() % 4 == 3) && (direction != EDirection::eWest))
	{
		direction = EDirection::eEast;
	}
	else if (isDead)
	{
		direction = EDirection::eStop;
	}

	//LEFT EDGE
	//Checks if ai is on left edge travelling towards it (west)
	if ((screenPos.x == 0) && (direction == EDirection::eWest))
	{
		std::cout << "AI ON LEFT EDGE" << std::endl;
		if (rand() % 4 != 0)
		{
			if (rand() % 2 == 0)
			{
				std::cout << "AI MOVING NORTH" << std::endl;
				direction = EDirection::eNorth;
			}
			else
			{
				std::cout << "AI MOVING SOUTH" << std::endl;
				direction = EDirection::eSouth;
			}
		}
		else
		{
			std::cout << "CONTINUING WEST" << std::endl;
		}
	}

	//Checks if ai is on left edge travelling parallel (north || south)
	if ((screenPos.x == 0) && (direction == EDirection::eNorth || direction == EDirection::eSouth))
	{
		std::cout << "AI PARALLEL LEFT EDGE" << std::endl;
		if (rand() % 4 != 0)
		{
			std::cout << "AI MOVING EAST" << std::endl;
			direction = EDirection::eEast;
		}
	}

	// RIGHT EDGE
	//Checks if ai is on right edge travelling towards it (east)
	if ((screenPos.x == 980) && (direction == EDirection::eEast))
	{
		std::cout << "AI ON RIGHT EDGE" << std::endl;
		if (rand() % 4 != 0)
		{
			if (rand() % 2 == 0)
			{
				std::cout << "AI MOVING NORTH" << std::endl;
				direction = EDirection::eNorth;
			}
			else
			{
				std::cout << "AI MOVING SOUTH" << std::endl;
				direction = EDirection::eSouth;
			}
		}
		else
		{
			std::cout << "CONTINUING EAST" << std::endl;
		}
	}

	//Checks if ai is on right edge travelling parallel (north || south)
	if ((screenPos.x == 980) && (direction == EDirection::eNorth || direction == EDirection::eSouth))
	{
		std::cout << "AI PARALLEL RIGHT EDGE" << std::endl;
		if (rand() % 4 != 0)
		{
			std::cout << "AI MOVING WEST" << std::endl;
			direction = EDirection::eWest;
		}
	}

	//BOTTOM EDGE
	//Checks if ai is on bottom edge travelling towards it (south)
	if ((screenPos.y == 730) && (direction == EDirection::eSouth))
	{
		std::cout << "AI ON BOTTOM EDGE" << std::endl;
		if (rand() % 4 != 0)
		{
			if (rand() % 2 == 0)
			{
				std::cout << "AI MOVING WEST" << std::endl;
				direction = EDirection::eWest;
			}
			else
			{
				std::cout << "AI MOVING EAST" << std::endl;
				direction = EDirection::eEast;
			}
		}
		else
		{
			std::cout << "CONTINUING SOUTH" << std::endl;
		}
	}

	//Checks if ai is on right edge travelling parallel (west || east)
	if ((screenPos.y == 730) && (direction == EDirection::eWest || direction == EDirection::eEast))
	{
		std::cout << "AI PARALLEL BOTTOM EDGE" << std::endl;
		if (rand() % 4 != 0)
		{
			std::cout << "AI MOVING NORTH" << std::endl;
			direction = EDirection::eNorth;
		}
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
	/*if (isAboveWater)
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
	}*/

	if (SegmentList.size() == 0) // Checks if snake is alive
	{
		isDead = true;
	}

	if (isDead)
	{
		Dead(window, score);
	}

	movementSteps++;
	//DisplayAir(window);
}

void AISnake::CollectableNorth()
{
	direction = EDirection::eNorth;
}

void AISnake::CollectableSouth()
{
	direction = EDirection::eSouth;
}

void AISnake::CollectableEast()
{
	direction = EDirection::eEast;
}

void AISnake::CollectableWest()
{
	direction = EDirection::eWest;
}

void AISnake::Dead(sf::RenderWindow & window, int &score)
{
	SegmentList.clear();
}
