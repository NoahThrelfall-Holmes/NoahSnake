#include "Game.h"
#include <iostream>
// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics/Text.hpp>

#include "Button.h"
#include "Slider.h"
#include "Switch.h"


Game::Game()
{
	m_foods.resize(m_numberOfFoods);
}

void Game::Setup()
{
	
	for (int i = 0; i < m_numberOfSnakes; i++)
	{
		sf::Vector2f pos;
		sf::Color col = sf::Color::Color(rand() % 255, rand() % 255, rand() % 255, 255);

		pos.x = (float)((rand() % 80) * 10);
		pos.y = (float)((rand() % 60) * 10);
		//std::cout << "snake pos: " << pos.x << ", " << pos.y << std::endl;
		snakes.push_back(new Snake(pos, 10, col, m_numberOfFoods, m_gobble));
		snakes[i]->m_name = i;
	}

	if (m_playerPlaying)
	{
		snakes[0]->m_isPlayer = true;
		//snakes[0]->SetColour(sf::Color::White);
		if (m_player2Playing)
		{
			snakes[1]->m_isPlayer2 = true;
		}
	}
	

	for (int i = 0; i < m_numberOfFoods; i++)
	{
		if (!m_foods[i].IsAlive())
		{
			sf::Vector2f pos;
			pos.x = (float)((rand() % 80) * 10);
			pos.y = (float)((rand() % 60) * 10);

			for (int j = 0; j < m_numberOfFoods; j++)
			{
				if (j != i)
				{
					if (pos == m_foods[j].GetPosition()) //Decreases but not negates chance of food spawning on top of each other at the start
														 //SpawnFood() function is far better as it is recursive until a clear spot is taken but at the start of the game this should be a minor issue
					{
						pos.x = (float)((rand() % 80) * 10);
						pos.y = (float)((rand() % 60) * 10);
					}
				}
			}
			
			m_foods[i].Spawn(pos, 10, sf::Color::Magenta);
			
			for (Snake* s : snakes)
				for (int j = 0; j < m_numberOfFoods; j++)
				{
					//std::cout << j << ": " << m_foods[j].IsAlive() << std::endl;
					s->UpdateFoodPositions(&m_foods[j], j);
				}
		}
	}
}

void Game::Run(sf::RenderWindow& window, bool& isRunning)
{
	// All SFML types and functions are contained in the sf namespace

	// Create an instance of the SFML RenderWindow type which represents the display
	// and initialise its size and title text
	

	// We can still output to the console window
	std::cout << "SnakeGame: Starting" << std::endl;

	m_playerPlaying = false;
	Setup();
	m_playerPlaying = true;

	sf::Clock clock;
	sf::Clock gameCounter;
	
	/* */sf::Texture titleTexture;
	titleTexture.loadFromFile("SFML/bin/data/images/Title.png");
	sf::Sprite titleSprite(titleTexture);
	titleSprite.move(-6.5, 0);

	//BUTTONS
	/* */sf::Texture playTexture1;
	playTexture1.loadFromFile("SFML/bin/data/images/PlayNormal.png");
	sf::Sprite playNormal(playTexture1);
	playNormal.setScale(0.75, 0.75);
	/* */sf::Texture playTexture2;
	playTexture2.loadFromFile("SFML/bin/data/images/PlayHighlighted.png");
	sf::Sprite playHighlighted(playTexture2);
	playHighlighted.setScale(0.75, 0.75);
	/* */sf::Texture playTexture3;
	playTexture3.loadFromFile("SFML/bin/data/images/PlayClicked.png");
	sf::Sprite playClicked(playTexture3);
	playClicked.setScale(0.75, 0.75);

	/* */sf::Texture exitTexture1;
	exitTexture1.loadFromFile("SFML/bin/data/images/ExitNormal.png");
	sf::Sprite exitNormal(exitTexture1);
	exitNormal.setScale(0.5, 0.5);
	/* */sf::Texture exitTexture2;
	exitTexture2.loadFromFile("SFML/bin/data/images/ExitHighlighted.png");
	sf::Sprite exitHighlighted(exitTexture2);
	exitHighlighted.setScale(0.5, 0.5);
	/* */sf::Texture exitTexture3;
	exitTexture3.loadFromFile("SFML/bin/data/images/ExitClicked.png");
	sf::Sprite exitClicked(exitTexture3);
	exitClicked.setScale(0.5, 0.5);

	/* */sf::Texture settingsTexture1;
	settingsTexture1.loadFromFile("SFML/bin/data/images/SettingsNormal.png");
	sf::Sprite settingsNormal(settingsTexture1);
	settingsNormal.setScale(0.5, 0.5);
	/* */sf::Texture settingsTexture2;
	settingsTexture2.loadFromFile("SFML/bin/data/images/SettingsHighlighted.png");
	sf::Sprite settingsHighlighted(settingsTexture2);
	settingsHighlighted.setScale(0.5, 0.5);
	/* */sf::Texture settingsTexture3;
	settingsTexture3.loadFromFile("SFML/bin/data/images/SettingsClicked.png");
	sf::Sprite settingsClicked(settingsTexture3);
	settingsClicked.setScale(0.5, 0.5);

	/* */sf::Texture backTexture1;
	backTexture1.loadFromFile("SFML/bin/data/images/BackNormal.png");
	sf::Sprite backNormal(backTexture1);
	backNormal.setScale(0.5, 0.5);
	/* */sf::Texture backTexture2;
	backTexture2.loadFromFile("SFML/bin/data/images/BackHighlighted.png");
	sf::Sprite backHighlighted(backTexture2);
	backHighlighted.setScale(0.5, 0.5);
	/* */sf::Texture backTexture3;
	backTexture3.loadFromFile("SFML/bin/data/images/BackClicked.png");
	sf::Sprite backClicked(backTexture3);
	backClicked.setScale(0.5, 0.5);

	Button startButton(400, 550, playNormal, playHighlighted, playClicked);
	Button exitButton(630, 550, exitNormal, exitHighlighted, exitClicked);
	Button settingsButton(100, 550, settingsNormal, settingsHighlighted, settingsClicked);
	Button backButton(100, 500, backNormal, backHighlighted, backClicked);

	//SLIDERS
	/* */sf::Texture sliderBarTexture;
	sliderBarTexture.loadFromFile("SFML/bin/data/images/SliderBar.png");
	sf::Sprite sliderBar(sliderBarTexture);
	/* */sf::Texture sliderHandleTexture;
	sliderHandleTexture.loadFromFile("SFML/bin/data/images/SliderHandle.png");
	sf::Sprite sliderHandle(sliderHandleTexture);

	/* */sf::Texture sliderBarTexture1;
	sliderBarTexture1.loadFromFile("SFML/bin/data/images/SliderBar.png");
	sf::Sprite sliderBar1(sliderBarTexture1);
	/* */sf::Texture sliderHandleTexture1;
	sliderHandleTexture1.loadFromFile("SFML/bin/data/images/SliderHandle.png");
	sf::Sprite sliderHandle1(sliderHandleTexture1);

	Slider snakeNumberSlider(400, 500, sliderHandle, sliderBar, m_numberOfSnakes, 2, 31);
	Slider gameSpeedSlider(400, 400, sliderHandle1, sliderBar1, m_gameSpeed, 1, 200);

	//TOGGLESS
	/* */sf::Texture switchOnTexture;
	switchOnTexture.loadFromFile("SFML/bin/data/images/SwitchYes.png");
	sf::Sprite switchOn(switchOnTexture);
	switchOn.setScale(0.5, 0.5);
	/* */sf::Texture switchOffTexture;
	switchOffTexture.loadFromFile("SFML/bin/data/images/SwitchNo.png");
	sf::Sprite switchOff(switchOffTexture);
	switchOff.setScale(0.5, 0.5);

	/* */sf::Texture switchOnTexture2;
	switchOnTexture2.loadFromFile("SFML/bin/data/images/SwitchYes.png");
	sf::Sprite switchOn2(switchOnTexture2);
	switchOn2.setScale(0.5, 0.5);
	/* */sf::Texture switchOffTexture2;
	switchOffTexture2.loadFromFile("SFML/bin/data/images/SwitchNo.png");
	sf::Sprite switchOff2(switchOffTexture2);
	switchOff2.setScale(0.5, 0.5);

	Switch togglePlayer(495, 245, switchOn, switchOff, m_playerPlaying);
	Switch togglePlayer2(495, 295, switchOn2, switchOff2, m_player2Playing);

	//TEXT
	sf::Font settingsFont;
	settingsFont.loadFromFile("SFML/bin/data/fonts/amazdoom/AmazDooMLeft.ttf");

	sf::Text numberOfSnakesText;
	numberOfSnakesText.setFont(settingsFont);
	std::string numberOfSnakesString = "Number of Snakes : ";
	numberOfSnakesString += std::to_string(m_numberOfSnakes);
	numberOfSnakesText.setString(numberOfSnakesString);
	numberOfSnakesText.setOrigin(numberOfSnakesText.getGlobalBounds().width / 2, numberOfSnakesText.getGlobalBounds().height / 2);
	numberOfSnakesText.setPosition(400, 470);

	sf::Text gameSpeedText;
	gameSpeedText.setFont(settingsFont);
	std::string gameSpeedString = "Game Speed : ";
	gameSpeedString += std::to_string(m_gameSpeed);
	gameSpeedText.setString(gameSpeedString);
	gameSpeedText.setOrigin(gameSpeedText.getGlobalBounds().width / 2, gameSpeedText.getGlobalBounds().height / 2);
	gameSpeedText.setPosition(400, 370);

	sf::Text togglePlayerText;
	togglePlayerText.setFont(settingsFont);
	togglePlayerText.setString("Generate Player Snake?");
	togglePlayerText.setOrigin(togglePlayerText.getGlobalBounds().width / 2, togglePlayerText.getGlobalBounds().height / 2);
	togglePlayerText.setPosition(370, 250);

	sf::Text togglePlayer2Text;
	togglePlayer2Text.setFont(settingsFont);
	togglePlayer2Text.setString("Generate Player 2 Snake?");
	togglePlayer2Text.setOrigin(togglePlayer2Text.getGlobalBounds().width / 2, togglePlayer2Text.getGlobalBounds().height / 2);
	togglePlayer2Text.setPosition(360, 300);

	//RANDOM
	sf::Texture speechBubbleTexture;
	speechBubbleTexture.loadFromFile("SFML/bin/data/images/SpeechBubble.png");
	sf::Sprite speechBubble(speechBubbleTexture);
	speechBubble.setScale(0.4, 0.4);
	sf::Text speechBubbleText;
	speechBubbleText.setFont(settingsFont);
	speechBubbleText.setString("You Are Here");
	speechBubbleText.setOrigin(speechBubbleText.getGlobalBounds().width / 2, speechBubbleText.getGlobalBounds().height / 2);

	sf::Texture speechBubble2Texture;
	speechBubble2Texture.loadFromFile("SFML/bin/data/images/SpeechBubble.png");
	sf::Sprite speechBubble2(speechBubble2Texture);
	speechBubble2.setScale(0.4, 0.4);
	sf::Text speechBubble2Text;
	speechBubble2Text.setFont(settingsFont);
	speechBubble2Text.setString("Player 2");
	speechBubble2Text.setOrigin(speechBubble2Text.getGlobalBounds().width / 2, speechBubble2Text.getGlobalBounds().height / 2);

	//SCORE BOARD
	sf::Texture scoreBoardTexture;
	scoreBoardTexture.loadFromFile("SFML/bin/data/images/ScoreBoard.png");
	sf::Sprite scoreBoard(scoreBoardTexture);
	scoreBoard.setPosition(800, 0);

	sf::Text scoreBoardTitle;
	scoreBoardTitle.setFont(settingsFont);
	scoreBoardTitle.setString(" SCORE BOARD ");
	scoreBoardTitle.setStyle(sf::Text::Style::Underlined);
	scoreBoardTitle.setOrigin(scoreBoardTitle.getGlobalBounds().width / 2, scoreBoardTitle.getGlobalBounds().height / 2);
	scoreBoardTitle.setPosition(950, 40);
	float defaultHeight = scoreBoardTitle.getGlobalBounds().height;
	float scoreBoardheight = window.getSize().y - 80 - defaultHeight;

	sf::Text displayTime;
	displayTime.setFont(settingsFont);
	std::string displayTimeString;
	displayTime.setString(displayTimeString);
	displayTime.setOrigin(displayTime.getGlobalBounds().width / 2, displayTime.getGlobalBounds().height / 2);
	displayTime.setPosition(950 - (scoreBoardTitle.getGlobalBounds().width), 30);

	Button scoreBoardBackButton(950 - backNormal.getGlobalBounds().width - 10, 550, backNormal, backHighlighted, backClicked);

	//GAMEOVER
	sf::Texture gameOverTexture;
	gameOverTexture.loadFromFile("SFML/bin/data/images/GameOver.png");
	sf::Sprite gameOver(gameOverTexture);
	gameOver.setOrigin(gameOver.getGlobalBounds().width / 2, gameOver.getGlobalBounds().height / 2);
	gameOver.setPosition(550, 300);

	sf::Text gameOverText;
	gameOverText.setFont(settingsFont);
	gameOverText.setString("-GAME OVER-");
	gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2, gameOverText.getGlobalBounds().height / 2);
	gameOverText.setPosition(550, 200);
	gameOverText.setScale(1.4, 1.4);


	Button gameOverBackButton(530, 440 - backNormal.getGlobalBounds().height, backNormal, backHighlighted, backClicked);

	while (isRunning)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				isRunning = false;
				break;
			default:
				break;
			}
		}

		//SIMULATION
		if (!isGameOver)
		{
			Rectangle boundary{ Point{400, 300}, 400 };
			QuadTree qtree(boundary, 4);
			std::list<Point> points;

			for (Snake* s : snakes)
			{
				s->Update();// (&qtree);
				for (size_t i = 0; i < s->m_segments.size(); i++)
				{
					auto it1 = std::next(s->m_segments.begin(), i);
					Point point{ it1->x, it1->y };
					qtree.Insert(&point);
				}
			}

			//Check Snake Collisions
			for (size_t i = 0; i < snakes.size(); i++)
			{
				if (snakes[i]->m_isDead)
				{
					snakes.erase(snakes.begin() + i);
					//std::cout << i << " IS DEAD" << std::endl;
				}

				for (size_t j = i + 1; j < snakes.size(); j++)
				{
					if (snakes[i]->CheckCollisions(*snakes[j]))
					{
						//std::cout << "HIT SNAKE" << std::endl;
						snakes.erase(snakes.begin() + i);
					}
					else if (snakes[j]->CheckCollisions(*snakes[i]))
					{
						//std::cout << "HIT SNAKE PRO" << std::endl;
						snakes.erase(snakes.begin() + j);
					}
				}

			}

			if (!m_gobble.IsAlive())
			{
				SpawnGobble(qtree, points, snakes);
			}

			if (rand() % 10 == 5)
			{

				for (int i = 0; i < m_numberOfFoods; i++)
				{
					//std::cout << "wtf" << std::endl;
					if (!m_foods[i].IsAlive())
					{
						SpawnFood(qtree, points, snakes, i);
					}
				}
			}
		}
		//VISUALISATION
		window.clear();

		for (Snake* s : snakes) {
			s->Render(window);
		}

		for (int i = 0; i < 5; i++)
		{
			if (m_foods[i].IsAlive())
			{
				m_foods[i].Render(window);
			}
		}

		if(m_gobble.IsAlive())
		{
			m_gobble.Render(window);
		}

		//UI VISUALISATION
		if (snakes[0]->m_isPlayer)
		{
			if (m_speechBubbleElapsedTime < m_speechBubbleWaitTime)
			{
				m_speechBubbleElapsedTime += 1;
				auto playerHead = snakes[0]->m_segments.begin();
				speechBubble.setPosition(*playerHead);
				speechBubbleText.setPosition(speechBubble.getPosition().x + speechBubble.getGlobalBounds().width / 2, speechBubble.getPosition().y + speechBubble.getGlobalBounds().height / 2);
				window.draw(speechBubble);
				window.draw(speechBubbleText);

				if (snakes[1]->m_isPlayer2) 
				{
					auto playerHead = snakes[1]->m_segments.begin();
					speechBubble2.setPosition(*playerHead);
					speechBubble2Text.setPosition(speechBubble2.getPosition().x + speechBubble2.getGlobalBounds().width / 2, speechBubble2.getPosition().y + speechBubble2.getGlobalBounds().height / 2);
					window.draw(speechBubble2);
					window.draw(speechBubble2Text);
				}
			}
		}

		if (m_elapsedTime < m_menuIdleWaitTime)
			m_elapsedTime += 1;

		if(m_elapsedTime >= m_menuIdleWaitTime)
		{
			if (titleSprite.getScale().x > 0.3)
			{
				titleSprite.scale(0.96, 0.96);
				titleSprite.move(0.2, 0);
			}
		}	

		window.draw(scoreBoard);
		window.draw(scoreBoardTitle);

		int count = 0;
		for (Snake* s : snakes)
		{
			if (!s->m_isDead)
			{
				count++;
				sf::Text displayScore;
				displayScore.setFont(settingsFont);
				std::string displayScoreString; 
				
				if (s->m_isPlayer2)
					displayScoreString = "Player 2 ";
				else if (s->m_isPlayer && !m_player2Playing)
					displayScoreString = "You ";
				else if (s->m_isPlayer && m_player2Playing)
					displayScoreString = "Player 1 ";
				else
				{
					displayScoreString = "Snake ";
					displayScoreString += std::to_string(s->m_name);
				}
				displayScoreString += " = ";
				displayScoreString += std::to_string(s->m_segments.size());
				displayScore.setString(displayScoreString);
				displayScore.setOrigin(displayScore.getGlobalBounds().width / 2, displayScore.getGlobalBounds().height / 2);
				float factor = 1 / defaultHeight;
				float newHeight = scoreBoardheight / snakes.size();
				if (newHeight > defaultHeight)
					newHeight = defaultHeight;
				sf::Vector2f newScale((factor* newHeight), (factor* newHeight));
				if (newScale.x > 1)
					newScale = sf::Vector2f(1, 1);
				displayScore.setScale(newScale);
				displayScore.setPosition(950, (20 + defaultHeight + (newHeight / 2)) + (newHeight * count));
				window.draw(displayScore);

				sf::RectangleShape shape;
				shape.setSize(sf::Vector2f(newHeight * 0.75, newHeight * 0.75));
				shape.setFillColor(s->GetColour());
				shape.setOrigin(shape.getGlobalBounds().width / 2, shape.getGlobalBounds().height / 2);
				shape.setPosition(950 - (displayScore.getGlobalBounds().width / 2) - shape.getSize().x, (20 + defaultHeight + (newHeight / 2)) + (newHeight * count));
				window.draw(shape);
			}		
		}

		if (isSettings)
		{
			window.draw(titleSprite);

			backButton.Update(window);
			if (backButton.m_isClicked)
				isMenu = true;

			snakeNumberSlider.Update(window);
			std::string numberOfSnakesString = "Number of Snakes : ";
			numberOfSnakesString += std::to_string(m_numberOfSnakes);
			numberOfSnakesText.setString(numberOfSnakesString);
			window.draw(numberOfSnakesText);

			gameSpeedSlider.Update(window);
			std::string gameSpeedString = "Game Speed : ";
			gameSpeedString += std::to_string(m_gameSpeed);
			gameSpeedText.setString(gameSpeedString);
			window.draw(gameSpeedText);

			togglePlayer.Update(window);
			window.draw(togglePlayerText);

			togglePlayer2.Update(window);
			window.draw(togglePlayer2Text);

			if (!m_playerPlaying)
				m_player2Playing = false;
		}
		
		if (isMenu)
		{	
			window.draw(titleSprite);

			startButton.Update(window);
			if (startButton.m_isClicked)
			{
				isMenu = false;
				for (Snake* s : snakes)
				{
					delete s;
					//delete[] s;
				}
				snakes.resize(0);
				m_foods.clear();
				m_foods.resize(m_numberOfFoods);
				isGame = true;
				gameCounter.restart();

				//scoreBoardBackButton

				Setup();
				m_speechBubbleElapsedTime = 0;
			}
			
			settingsButton.Update(window);
			if (!isSettings)
			{
				if (settingsButton.m_isClicked)
				{
					isMenu = false;
					isSettings = true;
					titleSprite.setScale(0.29, 0.29);
					titleSprite.setPosition(0, 0);
				}
			}
			else
				isSettings = false;
			
			exitButton.Update(window);
			if (exitButton.m_isClicked)
				isRunning = false;
		}
		
		if (isGame)
		{
			//Set-up Score Board
			displayTimeString = std::to_string((int)gameCounter.getElapsedTime().asSeconds());
			displayTime.setString(displayTimeString);
			window.draw(displayTime);

			scoreBoardBackButton.Update(window);
			if (scoreBoardBackButton.m_isClicked)
			{
				isGame = false;
				isMenu = true;
				for (Snake* s : snakes)
					delete s;
				snakes.resize(0);
				m_foods.clear();
				m_foods.resize(m_numberOfFoods);
				bool storeState = m_playerPlaying;
				bool storeStateDos = m_player2Playing;
				if (m_playerPlaying)
					m_playerPlaying = false;
				if (m_player2Playing)
					m_player2Playing = false;
				Setup();
				m_playerPlaying = storeState;
				m_player2Playing = storeStateDos;
			}

			if (gameCounter.getElapsedTime().asSeconds() >= 90)
			{
				isGame = false;
				isGameOver = true;
				gameCounter.restart();
			}
		}

		if (isGameOver) //FIX GAME ERROR WHEN FINAL SNAKE DIES + complete all specification conditions
		{
			window.clear();
			window.draw(gameOver);
			window.draw(gameOverText);
			gameOverBackButton.Update(window);

			int biggestSnakeSize{ 0 };
			std::vector<int> finalSnakeSizes;
			std::vector<Snake*> winningSnakes;
			for (Snake* s : snakes)
			{		
				finalSnakeSizes.push_back(s->m_segments.size());
				if (s->m_segments.size() > biggestSnakeSize) //Create draw condition display
				{
					biggestSnakeSize = s->m_segments.size();
				}
			}
			for (int i = 0; i < finalSnakeSizes.size(); i++)
			{
				if (biggestSnakeSize == finalSnakeSizes[i])
				{
					winningSnakes.push_back(snakes[i]);
				}
			}
			int count{ 0 };
			for (Snake* s : winningSnakes)
			{
				count++;
				sf::Text winnerText;
				winnerText.setFont(settingsFont);
				std::string winnerTextString;

				if (s->m_isPlayer2)
				{
					winnerTextString = "Winner - Player 2 ";
					winnerTextString += " = ";
					winnerTextString += std::to_string(s->m_segments.size());
				}
				else if (s->m_isPlayer && !m_player2Playing)
				{
					winnerTextString = "Winner - You ";
					winnerTextString += " = ";
					winnerTextString += std::to_string(s->m_segments.size());
				}
				else if (s->m_isPlayer && m_player2Playing)
				{
					winnerTextString = "Winner - Player 1 ";
					winnerTextString += " = ";
					winnerTextString += std::to_string(s->m_segments.size());
				}
				else
				{
					winnerTextString = "Winner - Snake ";
					winnerTextString += std::to_string(s->m_name);
					winnerTextString += " = ";
					winnerTextString += std::to_string(s->m_segments.size());
				}

				winnerText.setString(winnerTextString);
				winnerText.setOrigin(winnerText.getGlobalBounds().width / 2, winnerText.getGlobalBounds().height / 2);

				float factor = 1 / defaultHeight;
				float newHeight = 160 / winningSnakes.size();
				if (newHeight > defaultHeight)
					newHeight = defaultHeight;
				sf::Vector2f newScale((factor * newHeight), (factor * newHeight));
				if (newScale.x > 1)
					newScale = sf::Vector2f(1, 1);
				winnerText.setScale(newScale);
				winnerText.setPosition(550, 190 + (defaultHeight + (newHeight / 2)) + (newHeight * count));


				//winnerText.setPosition(550, 300 + (winnerText.getGlobalBounds().height * count));
				window.draw(winnerText);
			}
			
			if (gameOverBackButton.m_isClicked)
			{
				isGameOver = false;
				isMenu = true;
				for (Snake* s : snakes)
				{
					delete s;
					//delete[] s;
				}
				snakes.resize(0);
				m_foods.clear();
				m_foods.resize(m_numberOfFoods);
				gameCounter.restart();

				bool storeState = m_playerPlaying;
				bool storeStateDos = m_player2Playing;
				if(m_playerPlaying)
					m_playerPlaying = false;
				if (m_player2Playing)
					m_player2Playing = false;
				Setup();
				m_playerPlaying = storeState;
				m_player2Playing = storeStateDos;
			}
		}

		window.display();

		while (clock.getElapsedTime().asMilliseconds() < m_gameSpeed);

		window.clear();
		clock.restart();
	}

	std::cout << "SnakeGame: Finished" << std::endl;

	for (Snake* s : snakes)
	{
		delete s;
	}
	std::vector<Food>().swap(m_foods);
}


void Game::SpawnGobble(QuadTree& qtree, std::list<Point>& points, std::vector<Snake*>& snakes)
{
	sf::Vector2f pos;
	pos.x = (float)((rand() % 80) * 10);
	pos.y = (float)((rand() % 60) * 10);

	Rectangle range{ Point{(int)pos.x, (int)pos.y}, 10 };
	points = qtree.Query(range, &points);

	if (points.size() == 0) //Ensures spawn cannot occur where a snake body is
		m_gobble.Spawn(pos, 10, sf::Color::White);
	else
	{
		points.resize(0);
		SpawnGobble(qtree, points, snakes);	
		return;
	}		

	//Tell snakes where this is
	for (Snake* s : snakes)
		s->UpdateGobblePos(&m_gobble);
}

void Game::SpawnFood(QuadTree& qtree, std::list<Point>& points, std::vector<Snake*>& snakes, int& i)
{
	sf::Vector2f pos;
	pos.x = (float)((rand() % 80) * 10);
	pos.y = (float)((rand() % 60) * 10);

	//Stops Food spawning on top of a snakes body
	Rectangle range{ Point{(int)pos.x, (int)pos.y}, 10 };
	points = qtree.Query(range, &points);

	if (points.size() == 0)
		m_foods[i].Spawn(pos, 10, sf::Color::Magenta);
	else
	{
		points.resize(0);
		SpawnFood(qtree, points, snakes, i);
		return;
	}

	//Stops Food spawning on top of a food
	for (int j = 0; j < m_numberOfFoods; j++)
	{
		if (j != i)
		{
			if (pos == m_foods[j].GetPosition())
			{
				SpawnFood(qtree, points, snakes, i);
				return;
			}
		}
	}

	//Tell snakes where the food is
	for (Snake* s : snakes)
		for (int j = 0; j < m_numberOfFoods; j++)
			s->UpdateFoodPositions(&m_foods[j], j);
}

//I used this for "pos.x = (float)((rand() % 80) * 10)" but it was "pos.x = (float)(roundUp((rand() % 800), 10)"

//int Game::roundUp(int numToRound, int multiple)
//{
//	if (multiple == 0)
//		return numToRound;
//
//	int remainder = numToRound % multiple;
//	if (remainder == 0)
//		return numToRound;
//
//	return numToRound + multiple - remainder;
//}
