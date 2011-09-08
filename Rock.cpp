#include "Rock.h"
#include <iostream>
using namespace std;

const int tile_size = 50;

Rock::Rock(const Coordinate pos_x, const Coordinate pos_y): _pos_x(pos_x), _pos_y(pos_y)
{
	//throws an exception when no coordinate passed in is (0,0)
	if (_pos_x < 0 || _pos_y < 0) throw UndefinedRock();

	cout << "_pos_x: " << _pos_x << ", _pos_y: " << _pos_y << endl;
}

Coordinate Rock::get_x() const
{
	return _pos_x;
}

Coordinate Rock::get_y() const
{
	return _pos_y;
}
