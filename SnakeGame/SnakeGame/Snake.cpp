#include "Snake.h"
#include <stdlib.h>
#include <math.h>
#include <cmath>
#define M_PI 3.14159265358979323846

Snake::Snake(sf::Vector2f pos, float radius, sf::Color col, int numberOfFoods, Gobble& gobble) : m_radius(radius), m_colour(col)
{
	m_segments.push_back(pos);
	m_gobblePos = &gobble;
	m_direction = (EDirection)(rand() % 4);
	m_numberOfFoods = numberOfFoods;
	m_foods.resize(m_numberOfFoods);
	m_foodTarget = rand() % (m_numberOfFoods + 1);
	m_moveMode = rand() % 2;
	m_OGcolour = m_colour;
}

Snake::~Snake()
{
	std::list<sf::Vector2f>().swap(m_segments);
	std::vector<Food*>().swap(m_foods);
	
}

void Snake::Render(sf::RenderWindow& window)
{
	//sf::CircleShape shape(m_radius);
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(m_radius, m_radius));
	shape.setFillColor(m_colour);
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color::Black);
	//bool i = true;
	for (sf::Vector2f pos : m_segments)
	{
		shape.setPosition(pos);
		window.draw(shape);
	}	
}

void Snake::Update()//(QuadTree* globalQuadTree)
{
	sf::Vector2f pos = m_segments.front();
	sf::Vector2f OGpos = m_segments.front();

	if (m_foodTarget >= m_numberOfFoods)
	{
		//std::cout << "YES" << std::endl;
		m_target = m_gobblePos->GetPosition();
	}
	else if (m_foods[m_foodTarget]->IsAlive())
	{
		m_target = m_foods[m_foodTarget]->GetPosition();
	}
	else if (!m_foods[m_foodTarget]->IsAlive())
		m_foodTarget = rand() % (m_numberOfFoods + 1);

	if (m_gobbleMode)
	{
		if (m_gobbleTime > 0)
		{
			ColourUpdate();
			m_gobbleTime -= 1;
		}
		else
		{
			m_gobbleMode = false;
			m_gobbleTime = 100;
			m_colour = m_OGcolour;
		}
		//std::list<Point> points;
		//Rectangle range{ Point{(int)pos.x, (int)pos.y}, 100 };
		//points = globalQuadTree->Query(range, &points);
		//
		//if (points.size() > 0)
		//{
		//	for (Point p : points)
		//	{
		//		sf::Vector2f pPos{ (float)p.x, (float)p.y };
		//		for (sf::Vector2f segment : m_segments) {
		//			if (segment != pPos)
		//			{
		//				m_target = pPos;
		//				//break;
		//				//continue;
		//			}
		//			else if (m_foodTarget >= m_numberOfFoods)
		//			{
		//				//std::cout << "YES" << std::endl;
		//				m_target = m_gobblePos->GetPosition();
		//			}
		//			else if (m_foods[m_foodTarget]->IsAlive())
		//			{
		//				m_target = m_foods[m_foodTarget]->GetPosition();
		//			}
		//			else if (!m_foods[m_foodTarget]->IsAlive())
		//				m_foodTarget = rand() % (m_numberOfFoods + 1);
		//		}
		//		//break;
		//		//continue;
		//	}
		//}
	}

	//PLAYER MOVEMENT
	if (m_isPlayer)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && m_direction != (EDirection::eSouth)) //Secondary check means snake may not go back on itself
			ChangeDirection(EDirection::eNorth);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && m_direction != (EDirection::eEast))
			ChangeDirection(EDirection::eWest);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && m_direction != (EDirection::eNorth))
			ChangeDirection(EDirection::eSouth);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && m_direction != (EDirection::eWest))
			ChangeDirection(EDirection::eEast);
	}
	else if (m_isPlayer2)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && m_direction != (EDirection::eSouth)) //Secondary check means snake may not go back on itself
			ChangeDirection(EDirection::eNorth);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && m_direction != (EDirection::eEast))
			ChangeDirection(EDirection::eWest);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && m_direction != (EDirection::eNorth))
			ChangeDirection(EDirection::eSouth);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && m_direction != (EDirection::eWest))
			ChangeDirection(EDirection::eEast);
	}
	//AI MOVEMENT MODE 1 - results in straight lines towards target by using distance from target to calculate new direction
	else if (m_moveMode == 0)
	{
		//if (m_foods[m_foodTarget]->IsAlive() || m_foodTarget == 5) {
		sf::Vector2f dir{ (m_target.x - pos.x) / 10, (m_target.y - pos.y) / 10 };
		float dirMag = pow(dir.x, 2) + pow(dir.y, 2); //Dont need to sqaure root since im comparing squared to squared

		sf::Vector2f dirIfN{ dir.x    , dir.y + 1 }; float dirIfNMag = pow(dirIfN.x, 2) + pow(dirIfN.y, 2); //what line AB would be and its length if snake was 1 tile North
		sf::Vector2f dirIfE{ dir.x - 1, dir.y     }; float dirIfEMag = pow(dirIfE.x, 2) + pow(dirIfE.y, 2); //if snake was 1 tile East
		sf::Vector2f dirIfS{ dir.x    , dir.y - 1 }; float dirIfSMag = pow(dirIfS.x, 2) + pow(dirIfS.y, 2); //if snake was 1 tile South
		sf::Vector2f dirIfW{ dir.x + 1, dir.y     }; float dirIfWMag = pow(dirIfW.x, 2) + pow(dirIfW.y, 2); //if snake was 1 tile West

		if ((dirIfNMag < dirMag) && (m_direction != (EDirection::eSouth))) //Secondary check means snake may not go back on itself
			ChangeDirection(EDirection::eNorth); 		
		else if ((dirIfEMag < dirMag) && (m_direction != (EDirection::eWest)))
			ChangeDirection(EDirection::eEast); 		
		else if ((dirIfSMag < dirMag) && (m_direction != (EDirection::eNorth)))
			ChangeDirection(EDirection::eSouth);
		else if ((dirIfWMag < dirMag) && (m_direction != (EDirection::eEast)))
			ChangeDirection(EDirection::eWest);
		//}
	}
	//AI MOVEMENT MODE 2 - results in direct/wiggly lines towards target by using angle from A to B to calculate new direction
		//currently checks every tick meaning it will constantly move in relitively straight lines till ~45degrees
		//fixable by deciding path on the update it decides a new foodTarget and sticking to that path
			//not *harder* to implement but will completely change my logic so that can wait
				//maybe even have that as moveMode 3 uwu
	else if (m_moveMode == 1)
	{
		float dx = pos.x- m_target.x; //only seperated from atan2 calculation for ease of reading
		float dy = m_target.y - pos.y; //this too
		float theta = atan2(dy, dx); //angle towards B from A in radians

		if (theta < 0)
			theta = abs(theta);
		else
			theta = 2 * M_PI - theta;

		theta = theta * (180.0 / M_PI); //convert radians to degrees

		if (theta >= 45 && theta <= 135)			 //Initial check to see which direction the food is from the snake
			if (m_direction != (EDirection::eSouth)) //Secondary check means snake may not go back on itself
				ChangeDirection(EDirection::eNorth);
			else if (theta <= 90)					 //if snake would want to go back on itself but is unable to - move to the side
				ChangeDirection(EDirection::eWest);
			else
				ChangeDirection(EDirection::eEast);

		else if (theta > 135 && theta < 225)
			if (m_direction != (EDirection::eWest))
				ChangeDirection(EDirection::eEast);
			else if (theta <= 180)
				ChangeDirection(EDirection::eNorth);
			else
				ChangeDirection(EDirection::eSouth);

		else if (theta >= 225 && theta <= 315)
			if (m_direction != (EDirection::eNorth))
				ChangeDirection(EDirection::eSouth);
			else if (theta <= 270)
				ChangeDirection(EDirection::eEast);
			else
				ChangeDirection(EDirection::eWest);

		else if (theta > 315 || theta < 45)
			if (m_direction != (EDirection::eEast))
				ChangeDirection(EDirection::eWest);
			else if (theta < 360)
				ChangeDirection(EDirection::eSouth);
			else
				ChangeDirection(EDirection::eNorth);
	}

	switch (m_direction)
	{
	case EDirection::eNorth:
		pos.y -= m_radius;
		break;
	case EDirection::eEast:
		pos.x += m_radius;
		break;
	case EDirection::eSouth:
		pos.y += m_radius;
		break;
	case EDirection::eWest:
		pos.x -= m_radius;
		break;
	default:
		break;
	}

	//CHECK SELF COLLISIONS
	Rectangle boundary{ Point{400, 300}, 400 };
	QuadTree qtree(boundary, 3);

	if (CheckSelfCollisions(&qtree, &pos))
	{
		if (m_isPlayer || m_isPlayer2)
		{
			//std::cout << "SELF HIT" << std::endl;
			m_isDead = true;
		}
		else {
			CombatCollisions(&qtree, &OGpos, &pos);
		}
	}

	//CHECK FOOD COLLISIONS
	CheckFoodCollisions(&pos);

	//CHECK GOBBLE COLLISION
	if (pos == m_gobblePos->GetPosition()) 
	{
		if(m_gobbleMode)
			m_gobbleTime = 100;
		m_gobblePos->DeSpawn();
		m_foodTarget = rand() % (m_numberOfFoods + 1);
		m_moveMode = rand() % 2;
		m_gobbleMode = true;
	}

	//CHECK WALL COLLISIONS
	CheckWallCollisions(&pos);

	//UPDATE POSITION
	m_segments.push_front(pos);

	if(m_growAmount == 0){ m_segments.pop_back(); }
	else { m_growAmount--; }
}
//UPDATE END



//FUNCTIONS
void Snake::ChangeDirection(EDirection newDirection)
{
	m_direction = newDirection;
}

void Snake::UpdateFoodPositions(Food* food, int iteration)
{
	m_foods.resize(m_numberOfFoods);
	m_foods[iteration] = food;
}

void Snake::UpdateGobblePos(Gobble* pos)
{
	m_gobblePos = pos;
}

void Snake::SetColour(sf::Color newColour)
{
	m_colour = newColour;
	m_OGcolour = m_colour;
}

sf::Color Snake::GetColour()
{
	return m_colour;
}

void Snake::AddSegments(int numberToAdd)
{
	m_growAmount += numberToAdd;
}

void Snake::ColourUpdate()
{
	colourTicker++;

	switch (colourTicker)
	{
	case 0:
		m_colour = sf::Color::Red;
		break;
	case 1:
		m_colour = sf::Color(255, 122, 122, 255);
		break;
	case 2:
		m_colour = sf::Color::Yellow;
		break;
	case 3:
		m_colour = sf::Color::Green;
		break;
	case 4:
		m_colour = sf::Color::Blue;
		break;
	case 5:
		m_colour = sf::Color(138, 0, 255, 255);
		break;
	case 6:
		m_colour = m_OGcolour;

		colourTicker = 0;
		break;
	}
}

//COLLISION FUNCTIONS
void Snake::CheckFoodCollisions(sf::Vector2f* pos)
{
	Rectangle boundary{ Point{400, 300}, 400 }; //Point = centre of screen - 400 is both width and height
												//by having 400 as both width and height the quad tree is slghtly bigger than needed
												//by not having a global var for screen size i cannot change screen size without changes all of these boundary declarations
	QuadTree qtree(boundary, 3); // 3 = how many Points can be in a segment of the quad tree before it divides 
	std::list<Point> points;

	for (int i = 0; i < 5; i++)
	{
		//Creates a new point at the position of the food then places that into the quad tree which then automatically sorts itself
			//probably could have made the point struct a vector2 but it was easier to follow the psuedocode for quad trees by using the suggested 2 seperate ints
		Point point{ (int)m_foods[i]->GetPosition().x, (int)m_foods[i]->GetPosition().y };
		qtree.Insert(&point);
		Rectangle range{ Point{(int)pos->x, (int)pos->y}, 1 }; //Creates a rectangle at head pos and has a width and height of 1 / if any points are here they are equal to pos == foodPos 
		points = qtree.Query(range, &points);					//if any points appear within that range: add them to list

		if (points.size() > 0) //there is a point atop of headpos:
		{
			//m_foods.erase(m_foods.begin() + i);
			m_foods[i]->DeSpawn();
			AddSegments(m_foods[i]->m_score);
			m_foodTarget = rand() % (m_numberOfFoods + 1); //set new food to target
			m_moveMode = rand() % 2; //randomise which movestyle to use
			break;
		}
	}
}

void Snake::CheckWallCollisions(sf::Vector2f* pos)
{
	if (pos->x < 0 || pos->x > 790)
	{
		if (m_isPlayer || m_isPlayer2)
		{
			//std::cout << "WALL" << std::endl;
			m_isDead = true;
		}
		//STOP AI HITTING WALLS
		else {
			if (m_direction == EDirection::eEast)
				pos->x -= m_radius;
			else if (m_direction == EDirection::eWest)
				pos->x += m_radius;

			if (pos->y < 590) {
				pos->y += m_radius;
				m_direction = EDirection::eSouth;
			}
			else {
				pos->y -= m_radius;
				m_direction = EDirection::eNorth;
			}
		}
	}
	else if (pos->y < 0 || pos->y > 590)
	{
		if (m_isPlayer || m_isPlayer2)
		{
			//std::cout << "WALL" << std::endl;
			m_isDead = true;
		}
		//STOP AI HITTING WALLS
		else {
			if (m_direction == EDirection::eNorth)
				pos->y += m_radius;
			else if (m_direction == EDirection::eSouth)
				pos->y -= m_radius;

			if (pos->x < 790) {
				pos->x += m_radius;
				m_direction = EDirection::eEast;
			}
			else {
				pos->x -= m_radius;
				m_direction = EDirection::eWest;
			}
		}
	}

	if (pos->x < 0 || pos->x > 790)
		m_isDead = true;
	else if (pos->y < 0 || pos->y > 590)
		m_isDead = true;
}

bool Snake::CheckCollisions(Snake& other)
{
	Rectangle boundary{ Point{400, 300}, 400 };
	QuadTree qtree(boundary, 2);
	sf::Vector2f OGpos = m_segments.front();
	sf::Vector2f pos = m_segments.front();
	std::list<Point> points;

	switch (m_direction)
	{
	case EDirection::eNorth:
		OGpos.y += m_radius;
		break;
	case EDirection::eEast:
		OGpos.x -= m_radius;
		break;
	case EDirection::eSouth:
		OGpos.y -= m_radius;
		break;
	case EDirection::eWest:
		OGpos.x += m_radius;
		break;
	default:
		break;
	}

	for (int i = 0; i < other.m_segments.size(); i++) 
	{		
		auto it1 = std::next(other.m_segments.begin(), i);
		Point point{ (int)it1->x, (int)it1->y };
		qtree.Insert(&point);

		Rectangle range{ Point{(int)pos.x, (int)pos.y}, 1 };
		points = qtree.Query(range, &points);

		if (points.size() >= 1) {
			if (!m_gobbleMode)
			{
				if (m_isPlayer || m_isPlayer2)
				{
					points.clear();
					return true;
				}

				for (int i = 1; i < m_segments.size(); i++)
				{
					auto it2 = std::next(m_segments.begin(), i);
					Point point{ (int)it2->x, (int)it2->y };
					qtree.Insert(&point);
				}
				CombatCollisions(&qtree, &OGpos, &pos);
				auto it3 = std::next(m_segments.begin(), 0);
				m_segments.erase(it3);
				m_segments.push_front(pos);
				points.clear();
			}
			else 
			{
				int segmentsToRemove = other.m_segments.size() - i;
				if (segmentsToRemove < other.m_segments.size())
				{
					for (int j = 0; j < segmentsToRemove; j++)
					{
						other.m_segments.pop_back();
					}
					AddSegments(segmentsToRemove);
				}
				else
				{
					other.m_isDead = true;
					AddSegments(segmentsToRemove);
				}
			}
		}		
	}
	return false;
}

bool Snake::CheckSelfCollisions(QuadTree* qtree, sf::Vector2f* pos)
{
	std::list<Point> points;

	for (int i = 1; i < m_segments.size(); i++)
	{	
		auto it1 = std::next(m_segments.begin(), i);
		Point point{ (int)it1->x, (int)it1->y };
		qtree->Insert(&point);

		Rectangle range{ Point{(int)pos->x, (int)pos->y}, 1 };
		points = qtree->Query(range, &points);

		for (Point other : points) 
		{
			return true;
		}
		
	}
	return false;
}

void Snake::CombatCollisions(QuadTree* qtree, sf::Vector2f* pos, sf::Vector2f* finalPos) //pos is OGpos, so position before move, finalPos is new pos to move to
{
	sf::Vector2f posIfN{ pos->x, pos->y - 10 };
	sf::Vector2f posIfE{ pos->x + 10, pos->y };
	sf::Vector2f posIfS{ pos->x, pos->y + 10 };
	sf::Vector2f posIfW{ pos->x - 10, pos->y };

	sf::Vector2f Ndir{ 0, -10 };
	sf::Vector2f Edir{ 10, 0 };
	sf::Vector2f Sdir{ 0, 10 };
	sf::Vector2f Wdir{ -10, 0 };

	//This quad tree should already be filled with m_segments
	std::list<Point> points;
	std::list<sf::Vector2f> blocked;

	Rectangle range{ Point{(int)pos->x, (int)pos->y}, 19 };
	points = qtree->Query(range, &points);

	for (Point segment : points) 
	{
		sf::Vector2f aSegment{ (float)segment.x,  (float)segment.y };
		//int currDir = (int)EDirection(m_direction);

		if (*pos != aSegment)
			if (posIfN == aSegment || posIfE == aSegment || posIfS == aSegment || posIfW == aSegment)
			{
				//std::cout << "(" << segment.x << ", " << segment.y << ")" << std::endl;
				sf::Vector2f newDir{ aSegment.x - pos->x, aSegment.y - pos->y };
				blocked.push_back(newDir);
				//std::cout << "BLOCKED DIR: ";
				//std::cout << blocked.size() << std::endl;
			}
	}

	auto it1 = std::next(blocked.begin(), blocked.size() - blocked.size());
	auto it2 = std::next(blocked.begin(), blocked.size() - (blocked.size() - 1));

	auto it3 = std::next(blocked.begin(), 0);

	if (blocked.size() >= 4) {
		//std::cout << "ARGH" << std::endl;
		m_isDead = true;
		return;
	}
	if (blocked.size() == 3) {
		it3 = std::next(blocked.begin(), blocked.size() - (blocked.size() - 2));
		
		if(*it1 == Ndir || *it2 == Ndir || *it3 == Ndir)
			if (*it1 == Wdir || *it2 == Wdir || *it3 == Wdir)
				if (*it1 == Sdir || *it2 == Sdir || *it3 == Sdir){
					finalPos->x = pos->x += m_radius;
					finalPos->y = pos->y;
					m_direction = EDirection::eEast;
					return;
				}
		if (*it1 == Ndir || *it2 == Ndir || *it3 == Ndir)
			if (*it1 == Wdir || *it2 == Wdir || *it3 == Wdir)
				if (*it1 == Edir || *it2 == Edir || *it3 == Edir) {
					finalPos->y = pos->y += m_radius;
					finalPos->x = pos->x;
					m_direction = EDirection::eSouth;
					return;
				}
		if (*it1 == Ndir || *it2 == Ndir || *it3 == Ndir)
			if (*it1 == Edir || *it2 == Edir || *it3 == Edir)
				if (*it1 == Sdir || *it2 == Sdir || *it3 == Sdir) {
					finalPos->x = pos->x -= m_radius;
					finalPos->y = pos->y;
					m_direction = EDirection::eWest;
					return;
				}
		if (*it1 == Edir || *it2 == Edir || *it3 == Edir)
			if (*it1 == Wdir || *it2 == Wdir || *it3 == Wdir)
				if (*it1 == Sdir || *it2 == Sdir || *it3 == Sdir) {
					finalPos->y = pos->y -= m_radius;
					finalPos->x = pos->x;
					m_direction = EDirection::eNorth;
					return;
				}
	}
	if (blocked.size() == 2)
	{
		if (*it1 == Ndir || *it2 == Ndir)
			if (*it2 == Edir || *it1 == Edir)
				if (m_direction == EDirection::eNorth) {
					finalPos->y = pos->y += m_radius;
					finalPos->x = pos->x;
					m_direction = EDirection::eSouth;
					return;
				}
				else if (m_direction == EDirection::eEast) {

					finalPos->x = pos->x -= m_radius;
					finalPos->y = pos->y;
					m_direction = EDirection::eWest;
					return;
				}
		if (*it1 == Edir || *it2 == Edir)
			if (*it2 == Sdir || *it1 == Sdir)
				if (m_direction == EDirection::eEast) {
					finalPos->x = pos->x -= m_radius;
					finalPos->y = pos->y;
					m_direction = EDirection::eWest;
					return;
				}
				else if (m_direction == EDirection::eSouth) {
					finalPos->y = pos->y -= m_radius;
					finalPos->x = pos->x;
					m_direction = EDirection::eNorth;
					return;
				}
		if (*it1 == Sdir || *it2 == Sdir)
			if (*it2 == Wdir || *it1 == Wdir)
				if (m_direction == EDirection::eSouth) {
					finalPos->y = pos->y -= m_radius;
					finalPos->x = pos->x;
					m_direction = EDirection::eNorth;
					return;
				}
				else if (m_direction == EDirection::eWest) {
					finalPos->x = pos->x += m_radius;
					finalPos->y = pos->y;
					m_direction = EDirection::eEast;
					return;
				}
		if (*it1 == Wdir || *it2 == Wdir)
			if (*it2 == Ndir || *it1 == Ndir)
				if (m_direction == EDirection::eWest) {
					finalPos->x = pos->x += m_radius;
					finalPos->y = pos->y;
					m_direction = EDirection::eEast;
					return;
				}
				else if (m_direction == EDirection::eNorth) {
					finalPos->y = pos->y += m_radius;
					finalPos->x = pos->x;
					m_direction = EDirection::eSouth;
					return;
				}
		if (*it1 == Ndir || *it2 == Ndir)
			if (*it2 == Sdir || *it1 == Sdir)
				if (m_direction == EDirection::eSouth || m_direction == EDirection::eNorth)
				{
					if (m_moveMode == 0)
					{
						finalPos->x = pos->x += m_radius;
						finalPos->y = pos->y;
						m_direction = EDirection::eEast;
						return;
					}
					else
					{
						finalPos->x = pos->x -= m_radius;
						finalPos->y = pos->y;
						m_direction = EDirection::eWest;
						return;
					}
				}
		if (*it1 == Edir || *it2 == Edir)
			if (*it2 == Wdir || *it1 == Wdir)
				if (m_direction == EDirection::eWest || (m_direction == EDirection::eEast))
				{
					if (m_moveMode == 0)
					{
						finalPos->y = pos->y -= m_radius;
						finalPos->x = pos->x;
						m_direction = EDirection::eNorth;
						return;
					}
					else
					{
						finalPos->y = pos->y += m_radius;
						finalPos->x = pos->x;
						m_direction = EDirection::eSouth;
						return;
					}
				}
	}
	if (blocked.size() == 1)
	{
		if (*it1 == Ndir || *it1 == Sdir)
			if (m_moveMode == 0)
			{
				finalPos->x = pos->x += m_radius;
				finalPos->y = pos->y;
				m_direction = EDirection::eEast;
				return;
			}
			else
			{
				finalPos->x = pos->x -= m_radius;
				finalPos->y = pos->y;
				m_direction = EDirection::eWest;
				return;
			}
		if (*it1 == Edir || *it1 == Wdir)
			if (m_moveMode == 0)
			{
				finalPos->y = pos->y -= m_radius;
				finalPos->x = pos->x;
				m_direction = EDirection::eNorth;
				return;
			}
			else
			{
				finalPos->y = pos->y += m_radius;
				finalPos->x = pos->x;
				m_direction = EDirection::eSouth;
				return;
			}
	}
}



//void Snake::Kill()
//{
//	m_growAmount -= m_growAmount;
//
//}

