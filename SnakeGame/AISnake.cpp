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
		screenPos.y -= diameter;
		break;

	case EDirection::eSouth:
		screenPos.y += diameter;
		break;

	case EDirection::eEast:
		screenPos.x += diameter;
		break;

	case EDirection::eWest:
		screenPos.x -= diameter;
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

void AISnake::CollectableDistance(int& distance)
{
	AICollectableDistance.push_back(distance);
}

void AISnake::Pathfinding(std::vector<Collectable*>& collectableItems)
{
	for (int distanceIndex = 0; distanceIndex < AICollectableDistance.size(); distanceIndex++)
	{
		// Determines closest collectable
		if (AICollectableDistance[distanceIndex] < closestValue)
		{
			fifthClosestValue = fourthClosestValue;
			fifthClosestValuePos = fourthClosestValuePos;
			fourthClosestValue = thirdClosestValue;
			fourthClosestValuePos = thirdClosestValuePos;
			thirdClosestValue = secondClosestValue;
			thirdClosestValuePos = secondClosestValuePos;
			secondClosestValue = closestValue;
			secondClosestValuePos = closestValuePos;
			closestValue = AICollectableDistance[distanceIndex];
			closestValuePos = distanceIndex;
		}
	}
	
	// Checks collectable is active
	if (collectableItems[closestValuePos]->Alive())
	{
		AITargetCollectable = collectableItems[closestValuePos]->GetScreenPos();
	}
	else if (collectableItems[secondClosestValuePos]->Alive())
	{
		AITargetCollectable = collectableItems[secondClosestValuePos]->GetScreenPos();
	}
	else if (collectableItems[thirdClosestValuePos]->Alive())
	{
		AITargetCollectable = collectableItems[thirdClosestValuePos]->GetScreenPos();
	}
	else if (collectableItems[fourthClosestValuePos]->Alive())
	{
		AITargetCollectable = collectableItems[fourthClosestValuePos]->GetScreenPos();
	}
	else if (collectableItems[fifthClosestValuePos]->Alive())
	{
		AITargetCollectable = collectableItems[fifthClosestValuePos]->GetScreenPos();
	}
	else
	{
		AITargetCollectable = SetRandomDestination();
	}
	// Gets x and y distances and makes them positive if negative
	xTargetDistance = (int)GetScreenPos().x - (int)AITargetCollectable.x;
	if (xTargetDistance < 0)
	{
		xTargetDistance = -xTargetDistance;
	}
	yTargetDistance = (int)GetScreenPos().y - (int)AITargetCollectable.y;
	if (yTargetDistance < 0)
	{
		yTargetDistance = -yTargetDistance;
	}

	// Set direction to collectable
	if (xTargetDistance > yTargetDistance)
	{
		if (AITargetCollectable.x > GetScreenPos().x)
		{
			if (direction != EDirection::eWest)
			{
				CollectableEast();
			}
		}
		else
		{
			if (direction != EDirection::eEast)
			{
				CollectableWest();
			}
		}
	}
	else
	{
		if (AITargetCollectable.y > GetScreenPos().y)
		{
			if (direction != EDirection::eNorth)
			{
				CollectableSouth();
			}
		}
		else
		{
			if (direction != EDirection::eSouth)
			{
				CollectableNorth();
			}
		}
	}
}

void AISnake::Update(const int &screenWidth, const int &screenHeight, sf::RenderWindow & window, sf::Vector2f &waterScreenPos, std::vector<Collectable*>& collectableItems)
{
	AICollectableDistance.clear();

	//Checks if snake collides with window edges
	if (screenPos.x < 0 || screenPos.x > screenWidth - diameter)
	{
		isDead = true;
	}
	if (screenPos.y < 0 || screenPos.y > screenHeight - diameter)
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

	if (screenPos.x == screenWidth - diameter) // East edge
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

	if (screenPos.y == screenHeight - diameter) // South Edge
	{
		if (direction == EDirection::eSouth) //Heading towards edge
		{
			if (rand() % edgeChance != 0)
			{
				if ((rand() % 2 == 0) && (!isAboveWater))
				{
					direction = EDirection::eWest;
				}
				else
				{
					direction = EDirection::eEast;
				}
			}
		}
	}

	// Self Collision Check
	int index = 1;
	for (auto &segment : SegmentList)
	{
		// Skips the first element so the head isn't being compared to the head, only the body.
		if (index++ > 1)
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

	if ((!isAboveWater) && (movementSteps >= breathSteps - 20)) // Checks if snake is drowning
	{
		GoForAir();
	}

	if ((!isAboveWater) && (movementSteps >= breathSteps)) // Checks if snake is drowning
	{
		isDrowning = true;
		std::cout << "DROWNING" << std::endl;
	}

	if (isDrowning) // Removes a tail segment until surface is reached
	{
		GoForAir();

		if (movementSteps >= drowningSteps)
		{
			SegmentList.pop_back();
			movementSteps = 0; 
		}
	}

	if (SegmentList.size() == 0) // Checks if snake is alive
	{
		std::cout << "AI DROWNED" << std::endl;
		isDead = true;
	}

	if (isDead)
	{
		Dead();
	}

	movementSteps++;
	//DisplayAir(window);
}

void AISnake::AboveWater(const int &screenWidth)
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

void AISnake::GoForAir()
{
	direction = EDirection::eNorth;
}

bool AISnake::GetDrowning()
{
	return isDrowning;
}

int AISnake::GetMovementSteps()
{
	return movementSteps;
}

bool AISnake::PlayerCollision(sf::Vector2f& playerHeadPos)
{
	for (auto &segment : SegmentList)
	{
		if (segment == playerHeadPos)
		{
			isPlayerColliding = true;
			break;
		}
	}

	return isPlayerColliding;
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
	const float x = (float)(rand() % 1000);
	const float y = (float)(rand() % 750);

	sf::Vector2f randomDestination = { x,y };

	return randomDestination;
}

void AISnake::Dead()
{
	isDead = true;
	SegmentList.clear();
}
