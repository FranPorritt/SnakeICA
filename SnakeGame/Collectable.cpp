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
		isBonus = true;
	}
	else
	{
		color = sf::Color::Red;
		isBonus = false;
	}
}

Collectable::~Collectable()
{
}

bool Collectable::Alive()
{
	return aliveFlag;
}

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
	do
	{
		y = (rand() % 36) * 20;
	} while (y < water.GetScreenPos().y);

	screenPos = { x,y };
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

bool Collectable::GetBonus()
{
	return isBonus;
}
