#include "Rally_X.h"

void RallyX::displayErrorMessage(const string& message)
{
	al_show_native_message_box(NULL, NULL, NULL, message.c_str(), NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

SetupStatus RallyX::initialiseAllegroComponents()
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

SetupStatus RallyX::create_bitmaps()
{
	_bitmaps.road = al_create_bitmap(tile_size, tile_size);
	if(!_bitmaps.road) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      return DISPLAY_ERROR;
   }

	al_set_target_bitmap(_bitmaps.road);
   al_clear_to_color(al_map_rgb(255, 204, 51));
   al_set_target_bitmap(al_get_backbuffer(resources.display));

   _bitmaps.wall = al_create_bitmap(tile_size, tile_size);
	if(!_bitmaps.wall) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      return DISPLAY_ERROR;
   }

	al_set_target_bitmap(_bitmaps.wall);
	al_clear_to_color(al_map_rgb(51, 204, 51));
	al_set_target_bitmap(al_get_backbuffer(resources.display));

	_bitmaps.out_of_bounds = al_create_bitmap(tile_size, tile_size);
	if(!_bitmaps.out_of_bounds) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      return DISPLAY_ERROR;
   }

	al_set_target_bitmap(_bitmaps.out_of_bounds);
	al_clear_to_color(al_map_rgb(255, 51, 204));
	al_set_target_bitmap(al_get_backbuffer(resources.display));

	_bitmaps.player = al_create_bitmap(tile_size, tile_size);
	if(!_bitmaps.player) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      return DISPLAY_ERROR;
   }

	al_set_target_bitmap(_bitmaps.player);
	al_clear_to_color(al_map_rgb(0, 46, 184));
	al_set_target_bitmap(al_get_backbuffer(resources.display));

	return OKAY;
}

SetupStatus RallyX::allocateAllegroResources(AllegroResources& resources)
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


	create_bitmaps();

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

SetupStatus RallyX::setupAllegro(AllegroResources& resources)
{
	SetupStatus initialisation_status = initialiseAllegroComponents();
	if (initialisation_status == OKAY) 
		// allocate resources only after successful initialisation
		return allocateAllegroResources(resources);
	else
		return initialisation_status;
}

void RallyX::reportSetupError(SetupStatus status)
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


void RallyX::cleanup(AllegroResources& resources)
{
	// clean up memory allocated for the font, event_queue and display
	al_destroy_font(resources.font);	
	al_destroy_event_queue(resources.event_queue);
	al_destroy_display(resources.display);
	al_destroy_bitmap(_bitmaps.road);
	al_destroy_bitmap(_bitmaps.wall);
}

