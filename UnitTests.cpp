#include "Checkpoint.h"
#include "Map_Reader.h"
#include "Map.h"
#include <gtest/gtest.h>

using namespace std;

TEST(Checkpoint, onCreationThrowUndefinedCheckpoints) {  	
	EXPECT_THROW({Checkpoint testCheckpoint(-1, 2);}, UndefinedCheckpoint); 
}

TEST(Checkpoint, getXPosition){
	Checkpoint testCheckpoint(5, 2);
	EXPECT_TRUE(testCheckpoint.get_x() == 5);
}

TEST(Checkpoint, getYPosition){
	Checkpoint testCheckpoint(5, 2);
	EXPECT_TRUE(testCheckpoint.get_y() == 2);
}

TEST(Map_Reader, throwFileCannotBeOpened){
	MapReader _map_reader;
	EXPECT_THROW({_map_reader.loadFile("hello.txt");}, FileCannotBeOpened);
}

//TEST(Map_Reader, canReadInContent){
//	MapReader _map_reader;
//	_map_reader.loadFile("map_level_1.txt");
//	Map _game_map;
//	_map_reader.readInFile(_game_map);
//
//	EXPECT_TRUE(_game_map.get_row_length() > 1);
//}

TEST (Map_Reader, readInCorrectData){
	MapReader _map_reader;
	_map_reader.loadFile("map_level_1.txt");
	Map _game_map;
	_map_reader.readInFile(_game_map);
	
	EXPECT_TRUE(_game_map.get_tile(0,11) == 1);
	EXPECT_TRUE(_game_map.get_tile(0,10) == 0);
}

TEST (Map, getZeroIfOutOfBounds){
	MapReader _map_reader;
	_map_reader.loadFile("map_level_1.txt");
	Map _game_map;
	_map_reader.readInFile(_game_map);

	EXPECT_TRUE(_game_map.get_tile(50,50) == 0);
}

TEST (Map, canAddAndDeleteCheckpointsAtRightPlace){
	MapReader _map_reader;
	_map_reader.loadFile("map_level_1.txt");
	Map _game_map;
	_map_reader.readInFile(_game_map);

	vector<Checkpoint> all_checkpoints;
	int num_of_checkpoints = 10;

	vector <vector< tile_data_type> > tiled_map = _game_map.get_map();

	while (all_checkpoints.size() < num_of_checkpoints)							//to make sure always generate num_of_checkpoints
	{
		int col = rand()%(tiled_map.size()-1);
		int row = rand()%(tiled_map[col].size()-1);
				if (tiled_map[col][row] == 1)
				{
					Checkpoint newCheckpoint(col, row);
					all_checkpoints.push_back(newCheckpoint);
					_game_map.add_checkpoints(col, row);
					EXPECT_TRUE(_game_map.get_tile(col,row) == 5);
					_game_map.delete_checkpoints(col,row);
					EXPECT_TRUE(_game_map.get_tile(col,row) == 1);
				}
	}
}





