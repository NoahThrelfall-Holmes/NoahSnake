/*
  Games Development with C++ GAV1031-N
  Snake ICA start project 
  
  Set up to use the SFML 2.5.1 64-bit API
    SFML documentation: https://www.sfml-dev.org/learn.php
*/
#include <iostream>
#include <ctime>
#include "Game.h"
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1100, 600), "C++ Snake ICA : W9040509");
	srand(time(NULL));
	bool isRunning{ true };
	Game snakeGame;
	snakeGame.Run(window, isRunning);

    return 0;
}
