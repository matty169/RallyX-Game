#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include "Checkpoint.h"
#include "Rock.h"

using namespace std;

typedef int tile_data_type;
typedef vector <vector< tile_data_type> > Map_type;

class Map
{
public:

	Map();
	void add_row(string & string_row);

	void add_checkpoints(int pos_x, int pos_y);
	void delete_checkpoints(int pos_x, int pos_y);
	void add_rocks(int pos_x, int pos_y);
	void delete_rocks(int pos_x, int pos_y);

	Map_type get_map();
	static int get_row_length();
	int get_col_length();
	tile_data_type get_tile(Coordinate row, Coordinate col) const;

private:

	Map_type tiled_map;
	static int row_length;
	int col_length;
	tile_data_type tile;

};



#endif