#pragma once
#include <SFML/Graphics.hpp>

class Gobble
{
private:
	sf::Vector2f m_position;
	bool m_alive{ false };
	int m_radius{ 10 };
	sf::Color m_colour{ sf::Color::White };
public:
	int m_time{ 0 };
	bool IsAlive() const { return m_alive; }
	void Render(sf::RenderWindow& window);
	void Spawn(sf::Vector2f pos, int radius, sf::Color col);
	void DeSpawn();
	sf::Vector2f GetPosition();
};

