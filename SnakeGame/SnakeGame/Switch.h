#pragma once
#include <SFML/Graphics.hpp>

class Switch
{
private:
	float m_x;
	float m_y;
	float m_width;
	float m_height;

	bool* m_valueToChange;
	sf::Sprite* m_onSprite;
	sf::Sprite* m_offSprite;
public:
	Switch(float x, float y, sf::Sprite& on, sf::Sprite& off, bool& boolToChange);
	void Update(sf::RenderWindow& window);
};

