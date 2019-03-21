#include "Collectable.h"
#include "Water.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

Collectable::Collectable(sf::Vector2f screenPosArg, sf::Color colorArg, float radiusArg) :
	screenPos(screenPosArg), color(sf::Color::Red), radius(10.0f)
{
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
	srand(time(0));

	if (rand() % aliveCheckTime == 0)
	{
		aliveFlag = true;
	}
}

void Collectable::PickedUp(Water& water, int &screenHeight)
{
	aliveFlag = false;
	isPickedUp = true;
	NewScreenPos(screenPos, water, screenHeight);
}

void Collectable::Render(sf::RenderWindow& window, int &screenWidth, int &screenHeight)
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

sf::Vector2f Collectable::NewScreenPos(sf::Vector2f &screenPos, Water& water, int &screenHeight)
{
	float x = (rand() % 50 + 1) * 20; // FIX MAGIC NUMBERS
	float y = (rand() % 36 + 1) * 20;

	// Checks collectable doesn't spawn above water
	do
	{
		y = (rand() % 36 + 1) * 20;
	} while (y < water.GetScreenPos().y);

	screenPos = { x,y };
	isPickedUp = false;

	return screenPos;
}

sf::Vector2f Collectable::GetScreenPos()
{
	return screenPos;
}

void Collectable::Floating()
{
	screenPos.y += radius * 2;
}
