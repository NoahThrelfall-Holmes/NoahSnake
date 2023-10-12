#include "Slider.h"
#include <iostream>

Slider::Slider(float x, float y, sf::Sprite& handle, sf::Sprite& bar, int& valueToChange, int min, int max)
{
	m_x = x;
	m_y = y;
	m_sliderHandle = &handle;
	m_sliderBar = &bar;
	m_valueToChange = &valueToChange;
	m_minValue = min;
	m_maxValue = max;

	m_width = m_sliderHandle->getGlobalBounds().width;
	m_height = m_sliderHandle->getGlobalBounds().height;
	m_sliderHandle->setOrigin(m_width / 2, m_height / 2);
	m_width = m_sliderBar->getGlobalBounds().width;
	m_height = m_sliderBar->getGlobalBounds().height;
	m_sliderBar->setOrigin(m_width / 2, m_height / 2);

	m_sliderHandle->setPosition(m_x, m_y);
	m_sliderBar->setPosition(m_x, m_y);
}

void Slider::Update(sf::RenderWindow& window)
{
	sf::FloatRect boundaryBox = m_sliderBar->getGlobalBounds();
	if (boundaryBox.contains((sf::Vector2f)sf::Mouse::getPosition(window)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			m_sliderHandle->setPosition(sf::Mouse::getPosition(window).x, m_sliderHandle->getPosition().y);
		}
	}
	int start = (int)(m_sliderBar->getPosition().x - m_width / 2);
	int end = (int)(m_sliderBar->getPosition().x + m_width / 2);

	float yes = m_width / m_maxValue;
	//std::cout << yes << std::endl;

	*m_valueToChange = (int)((m_sliderHandle->getPosition().x - (start)) / yes);

	if (*m_valueToChange < m_minValue)
		*m_valueToChange = m_minValue;
	else if ((int)(m_sliderHandle->getPosition().x) >= end)
		*m_valueToChange = m_maxValue;

	window.draw(*m_sliderBar);
	window.draw(*m_sliderHandle);
}
