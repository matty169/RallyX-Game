#ifndef ALLEGRO_SETUP_H
#define ALLEGRO_SETUP_H


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5\allegro_native_dialog.h>
#include <string>

#include "colours.h"

using namespace std;

int const tile_size = 50;
int const FPS = 60;

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

// pointers to Allegro resources that are used in this program
struct AllegroResources
{
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_FONT* font;
	ALLEGRO_TIMER * timer;
	ALLEGRO_BITMAP * road;
	ALLEGRO_BITMAP * wall;
	ALLEGRO_BITMAP * out_of_bounds;
};

// displays an error message in a dialog box
void displayErrorMessage(const string& message)
{
	al_show_native_message_box(NULL, NULL, NULL, message.c_str(), NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

SetupStatus initialiseAllegroComponents()
{
	// initialise Allegro itself
	if(!al_init()) return ALLEGRO_INITIALISATION_ERROR;

	// initialise primitives addon (for drawing shapes)
	if(!al_init_primitives_addon()) return PRIMITIVES_ADDON_ERROR;

	// initialise font and ttf addon (for drawing text)
	al_init_font_addon();
	if (!al_init_ttf_addon()) return TTF_ADDON_ERROR;

	// install the keyboard
	if(!al_install_keyboard()) return KEYBOARD_ERROR;

	return OKAY;
}

SetupStatus allocateAllegroResources(AllegroResources& resources)
{
	// create the display
	resources.display = al_create_display(1024,750);
	if(!resources.display) return DISPLAY_ERROR;

	// create an event queue and register event sources
	resources.event_queue = al_create_event_queue();
	if(!resources.event_queue) 
	{
		// cleanup already allocated resources
		al_destroy_display(resources.display);
		return EVENT_QUEUE_ERROR;
	}


	resources.road = al_create_bitmap(tile_size, tile_size);
	if(!resources.road) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      return DISPLAY_ERROR;
   }

	al_set_target_bitmap(resources.road);
   al_clear_to_color(al_map_rgb(255, 204, 51));
   al_set_target_bitmap(al_get_backbuffer(resources.display));

   resources.wall = al_create_bitmap(tile_size, tile_size);
	if(!resources.wall) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      return DISPLAY_ERROR;
   }

	al_set_target_bitmap(resources.wall);
	al_clear_to_color(al_map_rgb(51, 204, 51));
	al_set_target_bitmap(al_get_backbuffer(resources.display));

	resources.out_of_bounds = al_create_bitmap(tile_size, tile_size);
	if(!resources.out_of_bounds) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      return DISPLAY_ERROR;
   }

	al_set_target_bitmap(resources.out_of_bounds);
	al_clear_to_color(al_map_rgb(255, 51, 204));
	al_set_target_bitmap(al_get_backbuffer(resources.display));

	resources.timer = al_create_timer(1.0 / FPS);


	al_register_event_source(resources.event_queue, al_get_keyboard_event_source());
	al_register_event_source(resources.event_queue, al_get_display_event_source(resources.display));
	al_register_event_source(resources.event_queue, al_get_timer_event_source(resources.timer));

	al_start_timer(resources.timer);

	// load font
	resources.font = al_load_font("data/arial.ttf", 18, 0);
	if (!resources.font)
	{
		// cleanup already allocated resources
		al_destroy_event_queue(resources.event_queue);
		al_destroy_display(resources.display);
		return FONT_LOADING_ERROR;
	}

	return OKAY;
}

SetupStatus setupAllegro(AllegroResources& resources)
{
	SetupStatus initialisation_status = initialiseAllegroComponents();
	if (initialisation_status == OKAY) 
		// allocate resources only after successful initialisation
		return allocateAllegroResources(resources);
	else
		return initialisation_status;
}

void reportSetupError(SetupStatus status)
{
	switch (status)
	{
	case ALLEGRO_INITIALISATION_ERROR:
		displayErrorMessage("Failed to initialize Allegro!");
		break;
	case PRIMITIVES_ADDON_ERROR:
		displayErrorMessage("Failed to initialize primitives add-on!");
		break;
	case TTF_ADDON_ERROR:
		displayErrorMessage("Failed to initialize TTF add-on!");
		break;
	case KEYBOARD_ERROR:
		displayErrorMessage("Failed to install keyboard driver!");
		break;
	case DISPLAY_ERROR:
		displayErrorMessage("Failed to create display!");
		break;
	case EVENT_QUEUE_ERROR:
		displayErrorMessage("Failed to create event_queue!");
		break;
	case FONT_LOADING_ERROR:
		displayErrorMessage("A font could not be loaded! Make sure that you copy the 'data' directory with the font file to the directory containing your project file (.vcxproj for Visual C++; .cbp for Code::Blocks).");
		break;            
	default:
		//should never reach here
		assert(false);
	}
}


void cleanup(AllegroResources& resources)
{
	// clean up memory allocated for the font, event_queue and display
	al_destroy_font(resources.font);	
	al_destroy_event_queue(resources.event_queue);
	al_destroy_display(resources.display);
	al_destroy_bitmap(resources.road);
	al_destroy_bitmap(resources.wall);
}


#endif