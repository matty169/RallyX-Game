#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

using namespace std;

typedef int tile_data_type;
typedef vector <vector< tile_data_type > > Map_type;

class Map
{
public:

	Map();
	void add_row(string & string_row);
	Map_type get_map();

private:

	Map_type tiled_map;

};



#endif