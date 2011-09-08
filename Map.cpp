#include "Map.h"
#include "Checkpoint.h"
#include <iostream>
#include <ctime>								//for random object generation

int Map::row_length = 0;
//int Map::num_of_checkpoints = 10;

Map::Map()
{
	srand(time(0));
}

void Map::add_row(string & string_row)
{
	vector <int> vec_row;
	string::iterator it;

	it = string_row.begin();
	while (it != string_row.end())
	{
		if (*it == '1')
			vec_row.push_back(1);
		else 
			vec_row.push_back(0);

		it++;
	}

	col_length = vec_row.size()-1;					//col_length different for all cols
	tiled_map.push_back(vec_row);
	row_length = tiled_map.size()-1;				//row_length will eventually be the same

	//Map::create_objects(string_row);				//create object for every row
}
void Map::add_checkpoints(int pos_x, int pos_y)
{
	tiled_map[pos_x][pos_y] = 5;
}

void Map::delete_checkpoints(int pos_x, int pos_y)
{
	tiled_map[pos_x][pos_y] = 1;
}

void Map::add_rocks(int pos_x, int pos_y)
{
	tiled_map[pos_x][pos_y] = 6;
}

void Map::delete_rocks(int pos_x, int pos_y)
{
	tiled_map[pos_x][pos_y] = 1;
}

Map_type Map::get_map()
{
	return tiled_map;
}

int Map::get_row_length()
{
	return row_length;
}

int Map::get_col_length()
{
	return col_length;
}
 
tile_data_type Map::get_tile(Coordinate row, Coordinate col) const
{
	if(row < 0 || col < 0)
		return 0;
	else if(row > tiled_map.size()-1)				//test if row is out of bounds
		return 0;
	else if (col > tiled_map[row].size()-1)
		return 0;
	else
		return tiled_map[row][col];
}
