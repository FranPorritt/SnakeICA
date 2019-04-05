#include "MenuSnake.h"

MenuSnake::MenuSnake(sf::Vector2f screenPosArg, sf::Color colorArg, float radiusArg) :
	Snake(screenPosArg, colorArg, radiusArg)
{
}

MenuSnake::~MenuSnake()
{
}

void MenuSnake::Wiggle()
{
	if (index % 2 == 0)
	{
		screenPos.y += 5.0f;
	}
	else
	{
		screenPos.y -= 5.0f;
	}
	index++;
}