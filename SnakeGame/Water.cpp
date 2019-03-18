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

sf::Vector2f Water::GetScreenPos()
{
	return waterScreenPos;
}