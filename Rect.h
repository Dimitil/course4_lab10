#pragma once
#include <math.h>

class Rect
{
	int _x;
	int _y;
	size_t _width;
	size_t _length;
public:
	Rect(int x = 10, int y = 10, size_t width = 10, size_t length = 10) : _x(x),
		_y(y), _width(width), _length(length) {}
	int getx() const { return _x; }
	int gety() const { return _y; }
};


class PredRectDistFromXY {
	int _x, _y;

	double distance(const Rect& r1) const
	{
		return sqrt(
			((_x - r1.getx()) * (_x - r1.getx())) +
			((_y - r1.gety()) * (_y - r1.gety()))
		);
	}

public:
	PredRectDistFromXY(int x = 0, int y = 0) : _x(x), _y(y) {}
	bool operator()(const Rect& r1, const Rect& r2) const
	{
		return distance(r1) < distance(r2);
	}
};