#pragma once

#include "Food.h"
#include "Gobble.h"
#include "Snake.h"

class Game
{
private:
	//int roundUp(int numToRound, int multiple);

	//Food m_food[5];
	Gobble m_gobble;

	bool isMenu{ true };
	bool isSettings{ false };
	bool isGame{ false };
	bool isGameOver{ false };

	int m_elapsedTime{ 0 };
	int m_menuIdleWaitTime{ 80 };
	int m_speechBubbleElapsedTime{ 0 };
	int m_speechBubbleWaitTime{ 30 };

	int m_gameSpeed{ 100 };
	int m_numberOfSnakes{ 15 };
	int m_numberOfFoods{ 5 };
	bool m_playerPlaying{ true };
	bool m_player2Playing{ false };

	std::vector<Food> m_foods;

	std::vector<Snake*> snakes;

	void SpawnGobble(QuadTree& qtree, std::list<Point>& points, std::vector<Snake*>& snakes);
	void SpawnFood(QuadTree& qtree, std::list<Point>& points, std::vector<Snake*>& snakes, int& i);
public:
	Game();
	void Run(sf::RenderWindow& window, bool& isRunning);
	void Setup();
};

