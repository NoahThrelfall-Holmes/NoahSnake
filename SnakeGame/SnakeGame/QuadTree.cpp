#include "QuadTree.h"

QuadTree::QuadTree(Rectangle boundary, int capacity) 
{
	if (capacity < 1)
		m_capacity = 1;
	else
		m_capacity = capacity;

	m_boundary = boundary;
	m_divided = false;
}

bool QuadTree::Insert(Point* point)
{
	if (!m_boundary.ContainsPoint(*point))
		return false;

	if (m_points.size() < m_capacity) {
		m_points.push_back(*point);
		return true;
	}

	if (!m_divided)
		Subdivide();

	return(northEast->Insert(point) || northWest->Insert(point) || southWest->Insert(point) || southEast->Insert(point));
}

std::list<Point> QuadTree::Query(Rectangle range, std::list<Point> *found)
{

	//std::list<Point> found;

	if (!m_boundary.IntersectsRectangle(range)) 
	{
		return *found;
	}
	for(Point p : m_points)
	{
		if (range.ContainsPoint(p))
			found->push_back(p);
	}
	if (m_divided) {
		northEast->Query(range, found);
		northWest->Query(range, found);
		southEast->Query(range, found);
		southWest->Query(range, found);
	}
	return *found;
}

void QuadTree::Subdivide() 
{
	int x = m_boundary.centre.x;
	int y = m_boundary.centre.y;
	int w = m_boundary.radius / 2;
	int h = m_boundary.radius / 2;

	Rectangle ne{ Point{x + w, y - h}, w };
	northEast = new QuadTree(ne, m_capacity);
	Rectangle nw{ Point{x - w, y - h}, w };
	northWest = new QuadTree(nw, m_capacity);
	Rectangle se{ Point{x + w, y + h}, w };
	southEast = new QuadTree(se, m_capacity);
	Rectangle sw{ Point{x - w, y + h}, w };
	southWest = new QuadTree(sw, m_capacity);

	m_divided = true;
}

QuadTree::~QuadTree()
{
	std::list<Point>().swap(m_points);
	if (m_divided)
	{
		delete(northEast);
		delete(northWest);
		delete(southEast);
		delete(southWest);
	}
	
	//delete(&m_boundary);
	//delete(&m_capacity);
	//delete(&m_divided);
}
