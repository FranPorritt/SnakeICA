#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"

class MenuSnake : public Snake
{
protected: 
	int index = 1;

public:
	MenuSnake(sf::Vector2f screenPosArg, sf::Color colorArg, float radiusArg);
	~MenuSnake();

	void Wiggle();
};

