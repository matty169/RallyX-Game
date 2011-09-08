#include "Map_Objects.h"

MapObjects::MapObjects(const Coordinate row, const Coordinate col): _row(row), _col(col)
{

}

Coordinate MapObjects::get_col()
{
	return _col;

}