#ifndef ROCK_H
#define ROCK_H

#include "Map_Objects.h"

typedef int Coordinate;

class Rock : public MapObjects
{
public:

	Rock(const Coordinate row, const Coordinate col)
		{
			MapObjects(row,col);
	};
	virtual void interaction_with_player();

private:
}



#endif