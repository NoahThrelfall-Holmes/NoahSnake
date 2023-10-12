#include "Food.h"

void Food::Render(sf::RenderWindow& window)
{
	//sf::CircleShape shape(m_radius);
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(m_radius, m_radius));
	shape.setFillColor(m_colour);
	shape.setPosition(m_position);

	window.draw(shape);
}

void Food::Spawn(sf::Vector2f pos, int radius, sf::Color col)
{
	m_position = pos;
	m_score = 1;
	m_radius = radius;
	m_colour = col;
	m_alive = true;
}

void Food::DeSpawn()
{
	m_alive = false;
}

sf::Vector2f Food::GetPosition()
{
	sf::Vector2f pos(m_position.x, m_position.y);
	return pos;
}


