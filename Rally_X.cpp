#include "Rally_X.h"
#include <iostream>

const int num_of_checkpoints = 10;
const int num_of_rocks = 5;

RallyX::RallyX()
{
	resources.display = NULL;
	resources.event_queue = NULL;
	resources.font = NULL;
	_bitmaps.out_of_bounds = NULL;
	_bitmaps.road = NULL;
	resources.timer = NULL;
	_bitmaps.wall = NULL;
	setup_allegro();
	Load_map("map_level_1.txt");

	tiled_map1 = _game_map.get_map();

	run_game();
}

void RallyX::setup_allegro()
{
	SetupStatus status = setupAllegro(resources);

	if (status != OKAY) 
	{
		reportSetupError(status);
		throw AllegroIncomplete();
	}

}

void RallyX::draw_viewport()
{


}

void RallyX::draw_info_board()
{
	al_draw_filled_rectangle(15*tile_size, 0, 1024, 15*tile_size, BLACK);

}


void RallyX::Load_map(const string& file_name)
{
	_map_reader.loadFile(file_name);
	_map_reader.readInFile(_game_map);
}

void RallyX::run_game()
{
	int player_x = 25;		// player co-ords on the map
	int player_y = 5;


	bool done = false;
	bool redraw = false;
	bool keys[4] = {false, false, false, false};
	bool player_movement[4] = {false, false, false, false};

	bitset<4> next_move ("0001");			// for movement; needs refinement...almost there tho...couple of hours...
	bitset<4> current_move ("0000");
	//keys = player_movement;

	int pos_x = 0;		// allows movement pixel wise, before changing position on the grid
	bitset<4> surrounding ("0000");

	int pos_y = 0;		// so movement is not jumpy by tile size

	int speed = 5;		// speed of movement between grid change



	////////////////////////////////////////////////

	// try to create checkpoints at random points, with a total num of 10
	// 10 is declared at the top of this file
	// this for-loop instantiate checkpoints and put them into a vector of checkpoints
	// while updating tiled_map1 by modifying _game_map to

	// still need to do: 
	// 1. destructors are called more than it's supposed to i.e. 9 times???
	// 2. try figure out a way to not let vector go out of bounds when destroying the last element
	// 3. _although make tiled_map1 = _game_map.get_map() in the end, map is still not updated??? i.e. still have checkpoint everywhere

	

	while (all_checkpoints.size() < num_of_checkpoints)							//to make sure always generate num_of_checkpoints
	{
		int col = rand()%(tiled_map1.size()-1);
		int row = rand()%(tiled_map1[col].size()-1);

		if (tiled_map1[col][row] == 1)
		{
			Checkpoint newCheckpoint(col, row);
			all_checkpoints.push_back(newCheckpoint);
			_game_map.add_checkpoints(col, row);
			//_game_map.delete_checkpoints(col,row);
		}
	}
	
	int added_rocks = 0;

	while (num_of_rocks > added_rocks)										
	{
		int col = rand()%(tiled_map1.size()-1);
		int row = rand()%(tiled_map1[col].size()-1);
		cout << "add rock!" << endl;

		if (tiled_map1[col][row] == 1)
		{
			Rock newRock(col, row);
			_game_map.add_rocks(col, row);
			//_game_map.delete_rocks(col,row);
			added_rocks ++;
		}
		
	}

	tiled_map1 = _game_map.get_map();									// HAVE TO KEEP ON UPDATING tiled_map1 otherwise new info cannot be loaded

	//////////////////////////////////////////////////////////////////


	while(!done)
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(resources.event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			next_move.reset();
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_UP:
				next_move[UP] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				next_move[RIGHT] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				next_move[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				next_move[LEFT] = true;
				break;
			}
		}

		surrounding[UP] =  tiled_map1[player_y - 1][player_x];		// must change so that a implementation of a 2d vector is unknown
		surrounding[RIGHT] =  tiled_map1[player_y][player_x + 1];
		surrounding[DOWN] =  tiled_map1[player_y + 1][player_x];
		surrounding[LEFT] =  tiled_map1[player_y][player_x - 1];

		if (pos_y == 0 && pos_x == 0)
		{
			/*if (next_move.none())
			{
				if ((current_move & ~(surrounding)).none())
					current_move >>=1;

			}
			else*/
			{
				current_move = next_move & surrounding; 
				//next_move.reset();
			}
		}


		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			pos_y += current_move[UP] * speed;		// if no movement will equal 0
			pos_y -= current_move[DOWN]  * speed;
			pos_x += current_move[LEFT]   * speed;
			pos_x -= current_move[RIGHT]  * speed;

			if (pos_y <= -(tile_size))		
			{
				pos_y = 0;
				player_y++;		// increase player on grid if movement between is the distance of the grid
			}
			else if (pos_y >= (tile_size))
			{
				pos_y = 0;
				player_y--;
			} 

			if (pos_x <= -(tile_size))
			{
				pos_x = 0;
				player_x++;
			}
			else if (pos_x >= (tile_size))
			{
				pos_x = 0;
				player_x--;
			} 

			redraw = true;
		}

		if(redraw && al_is_event_queue_empty(resources.event_queue))
		{
			redraw = false;

			al_clear_to_color(al_map_rgb(0,0,0));
			

			for (int irow = -1; irow != tiles_per_display + 1; irow++)		// always 17; due to viewport size and one extra on either side
			{
				for (int icol = -1; icol != tiles_per_display + 1; icol++) 
				{
					if ((player_y - 7 + irow < out_of_bounds_map) || (player_x - 7 + icol < out_of_bounds_map) ) 
					{
						al_draw_bitmap(_bitmaps.out_of_bounds, (icol * tile_size) + pos_x , (irow * tile_size) + pos_y, 0);		// draw bitmap with co-ordintes locked to the grid co-ords as well as distance traveled
					}
					else if (tiled_map1[player_y - 7 + irow][player_x - 7 + icol] == road_map)
					{
						al_draw_bitmap(_bitmaps.road, (icol * tile_size) + pos_x , (irow * tile_size) + pos_y, 0);
					}
					////////////////////////////////I PUT STUFF HERE///////////////////////////////////////////////////////
					else if(tiled_map1[player_y - 7 + irow][player_x - 7 + icol] == checkpoint_map)
					{
						al_draw_bitmap(_bitmaps.checkpoint, (icol * tile_size) + pos_x , (irow * tile_size) + pos_y, 0);
					}
					else if(tiled_map1[player_y - 7 + irow][player_x - 7 + icol] == rock_map)
					{
						al_draw_bitmap(_bitmaps.rock, (icol * tile_size) + pos_x , (irow * tile_size) + pos_y, 0);
					}
					
					////////////////////////////////I PUT STUFF HERE///////////////////////////////////////////////////////
					else
						al_draw_bitmap(_bitmaps.wall,(icol * tile_size) + pos_x, (irow * tile_size) + pos_y, 0);

				}

			}

			float pi = 3.1415926;
			al_draw_bitmap(_bitmaps.player, (7 * tile_size) , (7 * tile_size), 0);		// draw player car ( always in this position due to centered)
			al_draw_rotated_bitmap(_bitmaps.player, tile_size/2, tile_size/2, (7 * tile_size) , (7 * tile_size), pi, 0);		// draw player car ( always in this position due to centered)


			// if checkpoint is at the middle of the screen, call destroy_checkpoint
			// which calls the destructor, update the map and let player go one step closer to winning the game
			//for (int i = 0; i<Map::all_checkpoints.size(); i++)
			//{
			//	if (Map::all_checkpoints.)
			//}

			draw_info_board();

			al_flip_display();
		}
	}


}


