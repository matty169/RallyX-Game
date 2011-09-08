#ifndef ROCK_H
#define ROCK_H

#include <iostream>
using namespace std;

typedef int Coordinate;


class UndefinedRock {
//public:
//	void errorMessage();
};


class Rock
{
public:
	//constructor: accepts pos_x, pos_y from Game
	Rock(const Coordinate pos_x, const Coordinate pos_y);
	
	Coordinate get_x() const;
	Coordinate get_y() const;

	~Rock()	
	{
		cout << "destroying rock!" << endl;
	}

private:	
	Coordinate _pos_x;
	Coordinate _pos_y;
};

#endif