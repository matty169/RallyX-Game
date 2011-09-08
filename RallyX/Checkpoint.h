#ifndef CHECKPOINT_H
#define CHEKCPOINT_H

#include "Map_Objects.h"

class Checkpoint : public MapObjects
{
public:

	Checkpoint(const Coordinate, const Coordinate);
	virtual void interaction_with_player();

private:


};



#endif