#include "Collectable.h"
#include "Water.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

Collectable::Collectable(sf::Vector2f screenPosArg, float radiusArg) :
	screenPos(screenPosArg), radius(10.0f)
{
	if (rand() % 3 == 0)
	{
		color = sf::Color::White;
		isWhiteBonus = true;
		isPurpleBonus = false;
	}
	else if (rand() % 20 == 0)
	{
		color = sf::Color(138, 43, 226); // Purple
		isWhiteBonus = false;
		isPurpleBonus = true;
	}
	else
	{
		color = sf::Color::Red;
		isWhiteBonus = false;
		isPurpleBonus = false;
	}
}

Collectable::~Collectable()
{
}

// Checks if collectable is active
bool Collectable::Alive()
{
	return aliveFlag;
}

// Determines if a collectable is active or not
void Collectable::AliveCheck()
{
	if (rand() % aliveCheckTime == 0)
	{
		aliveFlag = true;
	}
}

void Collectable::PickedUp(Water& water, const int &screenHeight)
{
	aliveFlag = false;
	isPickedUp = true;
	NewScreenPos(screenPos, water, screenHeight);
}

void Collectable::Render(sf::RenderWindow& window, const int &screenWidth, const int &screenHeight)
{
	if (rand() % aliveCheckTime == 0)
	{
		AliveCheck();
	}

	if (aliveFlag)
	{
		sf::CircleShape shape(radius);
		shape.setPosition(screenPos);
		shape.setFillColor(color);
		window.draw(shape);
	}
}

sf::Vector2f Collectable::NewScreenPos(sf::Vector2f &screenPos, Water& water, const int &screenHeight)
{
	float x = (rand() % 50) * 20; // FIX MAGIC NUMBERS
	float y = (rand() % 36) * 20;

	// Checks collectable doesn't spawn above water
	if (water.GetScreenPos().y < 720)
	{
		do
		{
			y = (rand() % 36) * 20;
		} while (y < water.GetScreenPos().y);
	}
	else
	{
		y = 740;
	}

	screenPos = { x,y };

	if (rand() % 3 == 0)
	{
		color = sf::Color::White;
		isWhiteBonus = true;
		isPurpleBonus = false;
	}
	else if (rand() % 10 == 0)
	{
		color = sf::Color(138, 43, 226); // Purple
		isWhiteBonus = false;
		isPurpleBonus = true;
	}
	else
	{
		color = sf::Color::Red;
		isWhiteBonus = false;
		isPurpleBonus = false;
	}

	isPickedUp = false;

	return screenPos;
}

void Collectable::Floating()
{
	screenPos.y += radius * 2;
}

sf::Vector2f Collectable::GetScreenPos()
{
	return screenPos;
}

bool Collectable::GetWhiteBonus()
{
	return isWhiteBonus;
}

bool Collectable::GetPurpleBonus()
{
	return isPurpleBonus;
}