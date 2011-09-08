#include "Rally_X.h"
#include <iostream>
#include <math.h>

using namespace std;

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
	int player_x = 1;		// player co-ords on the map
	int player_y = 1;


	bool done = false;
	bool redraw = false;
	bool keys[4] = {false, false, false, false};
	bool player_movement[4] = {false, false, false, false};

	bitset<4> next_move ("0010");			// for movement; needs refinement...almost there tho...couple of hours...
	bitset<4> current_move ("0100");
	bitset<4> surrounding ("0000");
	bitset<4> temp ("0000");
	bitset<4> temp1 ("0000");

	bool turning_flag = false;
	int timer = 0;

	/*Checkpoint checkpoint1(0,1);

	cout <<checkpoint1.get_col() << endl;

	vector<MapObjects> objects;

	objects.push_back(Checkpoint(1,1));*/

	int pos_x = 0;		// allows movement pixel wise, before changing position on the grid
	int pos_y = 0;		// so movement is not jumpy by tile size

	int speed = 5;		// speed of movement between grid change

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

		//if (turning_flag)
		//	timer++;

		//if (timer == 20)
		//{
		//	turning_flag = false;
		//	timer = 0;
		//}

		if (pos_y == 0 && pos_x == 0)
		{
			
	
			if ( (next_move & surrounding).any() )
			{
				current_move = next_move;
				//break;
			}
			else if ( (current_move & surrounding).none() )
			{
				current_move <<= 1;				// can put this into another function which allows wrap around
				if (current_move.none())
					current_move[0] = 1;		// basically what this does
				next_move = current_move;
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
					if ((player_y - 7 + irow < 0) || (player_x - 7 + icol < 0) ) 
						al_draw_bitmap(_bitmaps.out_of_bounds, (icol * tile_size) + pos_x , (irow * tile_size) + pos_y, 0);		// draw bitmap with co-ordintes locked to the grid co-ords as well as distance traveled
					else if (tiled_map1[player_y - 7 + irow][player_x - 7 + icol] == 1)
						al_draw_bitmap(_bitmaps.road, (icol * tile_size) + pos_x , (irow * tile_size) + pos_y, 0);
					else
						al_draw_bitmap(_bitmaps.wall,(icol * tile_size) + pos_x, (irow * tile_size) + pos_y, 0);
				}

			}
			al_draw_bitmap(_bitmaps.player , (7 * tile_size) , (7 * tile_size),  0);
			al_draw_rotated_bitmap(_bitmaps.player, tile_size/2 , tile_size/2 , 0 , 0, 0,  0);		// draw player car ( always in this position due to centered)
			draw_info_board();

			al_flip_display();
		}
	}


}


