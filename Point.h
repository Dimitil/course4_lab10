#pragma once

#include <iostream>

class Point
{
	int _x = 0;
	int _y = 0;

public:
	Point(int x, int y) : _x(x), _y(y) {}
	bool operator<(const Point& p) const
	{
		return (_x + _y) < (p._x + p._y);
	}

	int getX() const { return _x; }
	int getY() const { return _y; }
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	
	friend std::ostream& operator<<(std::ostream& out, const Point& p)
	{
		out << "Point("<< p.getX() << ", " << p.getY() <<"}";
		return out;
	}

	bool operator==(const Point& p)
	{
		return _x == p._x && _y == p._y;
	}
};

class PredXYIn {
	int from;
	int to;
public:
	PredXYIn(int m, int n) : from(m), to(n) {}
	bool operator()(const Point& P) const
	{
		return P.getX() >= from &&
			P.getX() <= to &&
			P.getY() >= from &&
			P.getY() <= to;
	}
};