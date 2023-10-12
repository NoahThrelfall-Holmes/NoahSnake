#include "Switch.h"

Switch::Switch(float x, float y, sf::Sprite& on, sf::Sprite& off, bool& boolToChange)
{
	m_x = x;
	m_y = y;
	m_onSprite = &on;
	m_offSprite = &off;
	m_valueToChange = &boolToChange;

	m_width = m_onSprite->getGlobalBounds().width;
	m_height = m_onSprite->getGlobalBounds().height;
	m_onSprite->setOrigin(m_width / 2, m_height / 2);
	m_width = m_offSprite->getGlobalBounds().width;
	m_height = m_offSprite->getGlobalBounds().height;
	m_offSprite->setOrigin(m_width / 2, m_height / 2);

	m_onSprite->setPosition(m_x, m_y);
	m_offSprite->setPosition(m_x, m_y);
}

void Switch::Update(sf::RenderWindow& window)
{
	sf::Sprite* spriteToDraw;
	if (*m_valueToChange)
		spriteToDraw = m_onSprite;
	else
		spriteToDraw = m_offSprite;

	sf::FloatRect boundaryBox = m_offSprite->getGlobalBounds();
	if (boundaryBox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (*m_valueToChange)
			{
				*m_valueToChange = false;
				spriteToDraw = m_offSprite;
				return;
			}
			else
			{
				*m_valueToChange = true;
				spriteToDraw = m_onSprite;
				return;
			}
		}
	}	

	window.draw(*spriteToDraw);
}
