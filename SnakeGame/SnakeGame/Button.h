#pragma once
#include <SFML/Graphics.hpp>

class Button
{
private:
	float m_x; //position vector .x
	float m_y; //position vector .y
	float m_width; 
	float m_height;

	//Storage for the visualisation of the different states of the button
	sf::Sprite* m_normalSprite; 
	sf::Sprite* m_highlightedSprite;
	sf::Sprite *m_clickedSprite;
public:
	Button(float x, float y, sf::Sprite& normal, sf::Sprite& highlighted, sf::Sprite& clicked);
	void Update(sf::RenderWindow& window);
	bool m_isClicked{ false }; //public so that the script creating it can actually use the button in the code but should be really be a GetButton()
	//~Button();
};

