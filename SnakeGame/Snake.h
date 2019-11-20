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
	const float radius = 0;
	const float diameter = radius * 2;
	sf::Vector2f headPos;
	
	EDirection direction = EDirection::eNorth;	

	// Air variables
	int movementSteps = 0;
	int breathSteps = 100;
	int drowningSteps = 3;

	std::list<sf::Vector2f>SegmentList;
	int WhiteBonusLength = 3;
	int PurpleBonusLength = 7;
	int score = 0;
	
	bool isDead = false;
	bool isDrowning = false;
	bool isAboveWater = false;

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
	void GrowWhiteBonusTail();
	void GrowPurpleBonusTail();
	// Returns if dead
	bool DeadCheck();
	// Returns screen position
	sf::Vector2f GetScreenPos();
	// Return if colliding
	bool AICollision(sf::Vector2f& aiHeadPos);
	// Resets colliding bool to false
	void ResetCollision();
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
