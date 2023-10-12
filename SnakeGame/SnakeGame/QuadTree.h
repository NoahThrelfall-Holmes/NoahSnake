//https://en.wikipedia.org/wiki/Quadtree
#pragma once
#include <list>

struct Point {
	int x;
	int y;
};

struct Rectangle {
	Point centre;
	int radius;

	bool ContainsPoint(Point point) {
		return (point.x >= centre.x - radius &&
			point.x <= centre.x + radius &&
			point.y >= centre.y - radius &&
			point.y <= centre.y + radius);
	}

	bool IntersectsRectangle(Rectangle other) {
		return !(other.centre.x - other.radius > centre.x + radius ||
			other.centre.x + other.radius < centre.x - radius ||
			other.centre.y - other.radius > centre.y + radius ||
			other.centre.y + other.radius < centre.y - radius);
	}
};

class QuadTree
{
private:
	Rectangle m_boundary; //the area encompased by this quad
	int m_capacity; //how many points a quad can store before subdividing
	std::list<Point> m_points; //store of the point in this quad
	bool m_divided; //is this quad subdivided?

	// Children
	QuadTree* northWest;
	QuadTree* northEast;
	QuadTree* southWest;
	QuadTree* southEast;
public:
	QuadTree(Rectangle boundary, int capacity);
	bool Insert(Point* point);
	std::list<Point> Query(Rectangle range, std::list<Point> *found);
	void Subdivide();
	~QuadTree();
};

