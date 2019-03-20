#include "Water.h"

Water::Water(sf::Color colorArg, sf::Vector2f waterSizeArg) :
	color(colorArg), waterSize(waterSizeArg)
{
}

Water::~Water()
{
}

void Water::Render(sf::RenderWindow& window)
{
	sf::RectangleShape water(waterSize);
	water.setPosition(waterScreenPos);
	water.setFillColor(color);
	window.draw(water);
}

void Water::Leak()
{
	waterScreenPos.y += 20.0f;
}

void Water::MenuLeak()
{
	waterScreenPos.y += 0.5f;
}

void Water::MenuPos()
{
	waterScreenPos = { 0,450 };
}

sf::Vector2f Water::GetScreenPos()
{
	return waterScreenPos;
}