#ifndef RALLY_X_H
#define RALLY_X_H

#include "Map.h"
#include "Map_Reader.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h>
#include <string>
#include <bitset>

#include "colours.h"

class AllegroIncomplete{};  // Exception Class

int const tile_size = 50;
int const FPS = 60;
int const tiles_per_display = 15;

enum movement{ UP, RIGHT, DOWN, LEFT};


enum SetupStatus
{
	OKAY,
	ALLEGRO_INITIALISATION_ERROR,
	PRIMITIVES_ADDON_ERROR,
	TTF_ADDON_ERROR,
	KEYBOARD_ERROR,
	DISPLAY_ERROR,
	EVENT_QUEUE_ERROR,
	FONT_LOADING_ERROR
};

struct AllegroResources
{
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_FONT* font;
	ALLEGRO_TIMER * timer;
};

struct AllegroBitmaps
{
	ALLEGRO_BITMAP * road;
	ALLEGRO_BITMAP * wall;
	ALLEGRO_BITMAP * out_of_bounds;
	ALLEGRO_BITMAP * player;
	ALLEGRO_BITMAP * enemy;
	ALLEGRO_BITMAP * checkpoint;
	ALLEGRO_BITMAP * rock;
};

enum BitmapTypes
{
	wall_map,
	road_map,
	out_of_bounds_map,
	player_map,
	enemy_map,
	checkpoint_map,
	rock_map,
};

class RallyX
{
public:

	// setup functions
	RallyX();
	void setup_allegro();
	void Load_map(const string& file_name);

	// Allegro Setup Funtions
	SetupStatus initialiseAllegroComponents();
	SetupStatus allocateAllegroResources(AllegroResources& resources);
	SetupStatus setupAllegro(AllegroResources& resources);
	void reportSetupError(SetupStatus status);
	void cleanup(AllegroResources& resources);
	void displayErrorMessage(const string& message);
	SetupStatus create_bitmaps();

	void run_game();

	void draw_viewport();
	void draw_info_board();

private:
	Map _game_map;
	MapReader _map_reader;
	AllegroResources resources;
	AllegroBitmaps _bitmaps;
	Map_type tiled_map1;
	vector<Checkpoint> all_checkpoints;

};

#endif