#pragma once
#include <SFML/Graphics.hpp>

class Slider
{
private:
	float m_x;
	float m_y;
	float m_width;
	float m_height;
	
	int* m_valueToChange; //pointer as the slider itself edits the value and that change needs to be communicated to the original variable
	int m_minValue; //stored so that i have creative control over the resulting values of the slider from the calling of the constructor
	int m_maxValue;

	sf::Sprite* m_sliderHandle;
	sf::Sprite* m_sliderBar;
public:
	Slider(float x, float y, sf::Sprite& handle, sf::Sprite& bar, int& valueToChange, int min, int max);
	void Update(sf::RenderWindow& window);
};

