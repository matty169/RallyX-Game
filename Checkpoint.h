#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <iostream>
using namespace std;

typedef int Coordinate;


class UndefinedCheckpoint {
//public:
//	void errorMessage();
};


class Checkpoint
{
public:
	//constructor: accepts pos_x, pos_y from Game
	Checkpoint(const Coordinate pos_x, const Coordinate pos_y);
	
	Coordinate get_x() const;
	Coordinate get_y() const;

	~Checkpoint()	
	{
		cout << "destroying checkpoint!" << endl;
	}

private:	
	Coordinate _pos_x;
	Coordinate _pos_y;
};

#endif