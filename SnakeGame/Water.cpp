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
	waterScreenPos.y += leakRate;
}

void Water::MenuLeak()
{
	waterScreenPos.y += menuLeakRate;
}

void Water::MenuPos()
{
	waterScreenPos = { 0,450 };
}

sf::Vector2f Water::GetScreenPos()
{
	return waterScreenPos;
}