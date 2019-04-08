/*
  Games Development with C++ GAV1031-N
  Snake ICA start project 
  
  Set up to use the SFML 2.5.1 64-bit API
    SFML documentation: https://www.sfml-dev.org/learn.php
*/

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Snake.h"
#include "Collectable.h"

using namespace std;

int main()
{  
	sf::Vector2f waterScreenPos;
	const int screenWidth = 1000;
	const int screenHeight = 760;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "C++ Snake ICA : V8078659");

    // We can still output to the console window
    std::cout << "SnakeGame: Starting" << std::endl;

	Game* snakeGame = new Game();
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}
		}

		snakeGame->Update(window, screenWidth, screenHeight, waterScreenPos);

		if (snakeGame->GetRestart())
		{		
			snakeGame = new Game();
		}
	}

    std::cout << "SnakeGame: Finished" << std::endl;

	delete snakeGame;

    return 0;
}
