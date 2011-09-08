#ifndef MAP_OBJECTS_H
#define MAP_OBJECTS_H

typedef int Coordinate;

class MapObjects
{
public:
	MapObjects(const Coordinate, const Coordinate);
	Coordinate get_row();
	Coordinate get_col();
	virtual void interaction_with_player() = 0;


private:

	Coordinate _row;
	Coordinate _col;



};





#endif;