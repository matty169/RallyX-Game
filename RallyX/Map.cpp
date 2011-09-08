#include "Map.h"

Map::Map()
{

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

	tiled_map.push_back(vec_row);
}

Map_type Map::get_map()
{
	return tiled_map;

}

