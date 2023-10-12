#include "Button.h"
#include <iostream>

Button::Button(float x, float y, sf::Sprite& normal, sf::Sprite& highlighted, sf::Sprite& clicked)
{
	m_x = x;
	m_y = y;
	m_normalSprite = &normal;
	m_highlightedSprite = &highlighted;
	m_clickedSprite = &clicked;
	m_width = m_normalSprite->getGlobalBounds().width;
	m_height = m_normalSprite->getGlobalBounds().height;
}

void Button::Update(sf::RenderWindow& window)
{
	m_isClicked = false;
	sf::Sprite* spriteToDraw{m_normalSprite};

	sf::FloatRect boundaryBox = m_normalSprite->getGlobalBounds();
	if (boundaryBox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
	{
		spriteToDraw = m_highlightedSprite;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
		{
			spriteToDraw = m_clickedSprite;
			m_isClicked = true;
			//std::cout << "Clicked" << std::endl;
		}
	}
	spriteToDraw->setOrigin(m_width / 2, m_height / 2);
	spriteToDraw->setPosition(m_x, m_y);
	
	window.draw(*spriteToDraw);
}

//Button::~Button()
//{
//}
