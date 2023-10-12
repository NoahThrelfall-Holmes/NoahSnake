#include "Gobble.h"

void Gobble::Render(sf::RenderWindow& window)
{
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(m_radius, m_radius));
	shape.setFillColor(m_colour);
	shape.setPosition(m_position);

	window.draw(shape);
}

void Gobble::Spawn(sf::Vector2f pos, int radius, sf::Color col)
{
	m_position = pos;
	m_radius = radius;
	m_colour = col;
	m_alive = true;
}

void Gobble::DeSpawn()
{
	m_alive = false;
}

sf::Vector2f Gobble::GetPosition()
{
	sf::Vector2f pos(m_position.x, m_position.y);
	return pos;
}
