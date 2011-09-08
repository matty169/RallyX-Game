#ifndef MAP_READER_H
#define MAP_READER_H


#include <string>
#include <vector>
#include <fstream>
#include "Map.h"
using namespace std;

typedef int Coordinate;

// exception class
class FileCannotBeOpened{};

class MapReader
{
public:	
	void loadFile(const string& filename);
	void readInFile(Map& file_receiver);

private:	
	ifstream infile; // input file stream
};



#endif