#pragma once
#include <SFML/Graphics.hpp>
#include <list>

// Make tail segments a vector, each pick add an element to the vector which creates a new segment

enum class EDirection
{
	eNorth,
	eEast,
	eSouth,
	eWest,
	eStop
};

class Snake
{
protected:
	sf::Vector2f screenPos;
	sf::Color color;
	float radius;
	
	EDirection direction{ EDirection::eNorth };

	bool isDead = false;
	bool isDrowning = false;
	bool isAboveWater = false;

	int movementSteps = 0;
	int breathSteps = 100;
	int drowningSteps = 10;

	std::list<sf::Vector2f>SegmentList;
	int score;

public:
	Snake(sf::Vector2f screenPosArg, sf::Color colorArg, float radiusArg);
	~Snake();

	// Draws snake
	void Render(sf::RenderWindow& window);
	// Controls movement
	virtual void Move();
	// Checks if snake is alive
	virtual void Update(int &screenWidth, int &screenHeight, sf::RenderWindow & window, sf::Vector2f &waterScreenPos);
	// Called when snake is above water
	void AboveWater(int &screenWidth);
	void BelowWater();
	// Stops snake going more the one above the water level
	void Floating();
	// Adds new segment to snake
	void GrowTail();
	// Ends game
	virtual void Dead(sf::RenderWindow & window, int &score);
	// Returns screen position
	sf::Vector2f GetScreenPos();

	//SFML Rendering

	//Displays air remaining
	void DisplayAir(sf::RenderWindow & window);
	//Displays drowning warning
	void DrowningText(sf::RenderWindow & window);
};
