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
	eStop,
};

class Snake
{
protected:
	sf::Vector2f screenPos;
	sf::Color color;
	float radius;
	sf::Vector2f headPos;
	
	EDirection direction = EDirection::eNorth;

	bool isDead = false;
	bool isDrowning = false;
	bool isAboveWater = false;

	// Air variables
	int movementSteps = 0;
	int breathSteps = 100;
	int drowningSteps = 5;

	std::list<sf::Vector2f>SegmentList;
	int BonusLength = 5;
	int score = 0;

	bool isAIColliding = false;

public:
	Snake(sf::Vector2f screenPosArg, sf::Color colorArg, float radiusArg);
	~Snake();

	// Draws snake
	void Render(sf::RenderWindow& window);
	// Controls movement
	virtual void Move();
	// Checks if snake is alive
	virtual void Update(const int &screenWidth, const int &screenHeight, sf::RenderWindow & window, sf::Vector2f &waterScreenPos);
	// Called when snake is above water
	virtual void AboveWater(const int &screenWidth);
	virtual void BelowWater();
	// Stops snake going more the one above the water level
	void Floating();
	// Adds new segment to snake
	void GrowTail();
	// Adds multiple new segments to snake
	void GrowBonusTail();
	// Returns if dead
	bool DeadCheck();
	// Returns screen position
	sf::Vector2f GetScreenPos();
	bool AICollision(sf::Vector2f& aiHeadPos);
	// Returns head screen position
	sf::Vector2f GetHeadPos();
	// Returns player score
	int GetScore();

	//SFML Rendering

	//Displays air remaining
	void DisplayAir(sf::RenderWindow & window);
	// Displays Score
	void DisplayScore(sf::RenderWindow & window);
	//Displays drowning warning
	void DrowningText(sf::RenderWindow & window);
};
