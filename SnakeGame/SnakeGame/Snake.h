#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include "Food.h"
#include "Gobble.h"
#include "QuadTree.h"

enum class EDirection 
{
	eNorth,
	eEast,
	eSouth,
	eWest
};


class Snake
{
private:
	float m_radius{ 10 };
	sf::Color m_colour{ sf::Color::Blue };
	EDirection m_direction{ EDirection::eNorth };	
	int m_moveMode{ 1 };
	int m_growAmount{ 4 };
	
	std::vector<Food*> m_foods;
	
	int m_foodTarget{ 0 };
	sf::Vector2f m_target;
	Gobble* m_gobblePos;
	bool m_gobbleMode{ false };
	int m_gobbleTime{ 100 };
	sf::Color m_OGcolour;
	int colourTicker{ 0 };
	void ColourUpdate();
	void AddSegments(int numberToAdd);	
	
	
public:
	int m_name;
	std::list<sf::Vector2f> m_segments;
	bool m_isPlayer{ false };
	bool m_isPlayer2{ false };
	bool m_isDead{ false };
	int m_numberOfFoods;
	Snake(sf::Vector2f pos, float radius, sf::Color col, int numberOfFoods, Gobble &gobble);
	~Snake();
	void ChangeDirection(EDirection newdirection);
	void Update();//(QuadTree* globalQuadTree);
	void Render(sf::RenderWindow& window);
	void UpdateFoodPositions(Food* food, int iteration);
	void UpdateGobblePos(Gobble* pos);
	void CheckFoodCollisions(sf::Vector2f* pos);
	void CheckWallCollisions(sf::Vector2f* pos);
	bool CheckCollisions(Snake& other);
	bool CheckSelfCollisions(QuadTree* qtree, sf::Vector2f* pos);
	void CombatCollisions(QuadTree* qtree, sf::Vector2f* pos, sf::Vector2f* finalPos);
	void SetColour(sf::Color newColour);
	sf::Color GetColour();
	//void Kill();
};

