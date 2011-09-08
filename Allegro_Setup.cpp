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
	// Road
	_bitmaps.road = al_create_bitmap(tile_size, tile_size);
	if(!_bitmaps.road) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      return DISPLAY_ERROR;
	}

	al_set_target_bitmap(_bitmaps.road);
	al_clear_to_color(al_map_rgb(255, 204, 51));
	al_set_target_bitmap(al_get_backbuffer(resources.display));

	// Wall
	_bitmaps.wall = al_create_bitmap(tile_size, tile_size);
	if(!_bitmaps.wall) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      return DISPLAY_ERROR;
	}

	al_set_target_bitmap(_bitmaps.wall);
	al_clear_to_color(al_map_rgb(51, 204, 51));
	al_set_target_bitmap(al_get_backbuffer(resources.display));

	//out of bounds
	_bitmaps.out_of_bounds = al_create_bitmap(tile_size, tile_size);
	if(!_bitmaps.out_of_bounds) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      return DISPLAY_ERROR;
	}

	al_set_target_bitmap(_bitmaps.out_of_bounds);
	al_clear_to_color(al_map_rgb(255, 51, 204));
	al_set_target_bitmap(al_get_backbuffer(resources.display));

	
	//Where Merelda put stuff in!!!!!///////////////////////////////////////////
	//Where Merelda put stuff in!!!!!///////////////////////////////////////////
	//Where Merelda put stuff in!!!!!///////////////////////////////////////////
	//Where Merelda put stuff in!!!!!///////////////////////////////////////////
	//Where Merelda put stuff in!!!!!///////////////////////////////////////////

	//player
	_bitmaps.player = al_create_bitmap(tile_size, tile_size);
	if(!_bitmaps.player) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      return DISPLAY_ERROR;
	}

	al_set_target_bitmap(_bitmaps.player);
	al_clear_to_color(al_map_rgb(255, 204, 51));
	al_draw_filled_rounded_rectangle(13, 14, 43, 16, 1, 1, BLUE);				//front wheel bar
	al_draw_filled_rounded_rectangle(7, 10, 14, 20, 1, 1, BLACK);				//front wheel left
	al_draw_filled_rounded_rectangle(36, 10, 43, 20, 1, 1, BLACK);				//front wheel right
	al_draw_filled_rounded_rectangle(11, 32, 45, 34, 1, 1, BLUE);				//back wheel bar
	al_draw_filled_rounded_rectangle(5, 28, 12, 38, 1, 1, BLACK);				//back wheel left
	al_draw_filled_rounded_rectangle(38, 28, 45, 38, 1, 1, BLACK);				//back wheel right
	al_draw_filled_rounded_rectangle(20, 2, 30, 6, 1, 1, BLUE);					//little tip
	al_draw_filled_rounded_rectangle(16, 5, 34, 26, 2, 2, BLUE);				//front
	al_draw_filled_rounded_rectangle(13, 24, 37, 42, 2, 2, BLUE);				//middle
	al_draw_filled_rounded_rectangle(21, 16, 28, 37, 2, 2, WHITE);
	al_draw_filled_rectangle(20, 37, 22, 47, BLACK);			
	al_draw_filled_rectangle(27, 37, 29, 47, BLACK);
	al_set_target_bitmap(al_get_backbuffer(resources.display));

	
	
	//enemy
	_bitmaps.enemy = al_create_bitmap(tile_size, tile_size);
	if(!_bitmaps.enemy) {
      fprintf(stderr, "failed to create enemy bitmap!\n");
      return DISPLAY_ERROR;
	}

	al_set_target_bitmap(_bitmaps.enemy);
	al_clear_to_color(al_map_rgb(255, 204, 51));
	al_draw_filled_rounded_rectangle(13, 14, 43, 16, 1, 1, RED);				//front wheel bar
	al_draw_filled_rounded_rectangle(7, 10, 14, 20, 1, 1, BLACK);				//front wheel left
	al_draw_filled_rounded_rectangle(36, 10, 43, 20, 1, 1, BLACK);				//front wheel right
	al_draw_filled_rounded_rectangle(11, 32, 45, 34, 1, 1, RED);				//back wheel bar
	al_draw_filled_rounded_rectangle(5, 28, 12, 38, 1, 1, BLACK);				//back wheel left
	al_draw_filled_rounded_rectangle(38, 28, 45, 38, 1, 1, BLACK);				//back wheel right
	al_draw_filled_rounded_rectangle(20, 2, 30, 6, 1, 1, RED);					//little tip
	al_draw_filled_rounded_rectangle(16, 5, 34, 26, 2, 2, RED);					//front
	al_draw_filled_rounded_rectangle(13, 24, 37, 42, 2, 2, RED);				//middle
	al_draw_filled_rounded_rectangle(21, 16, 28, 37, 2, 2, WHITE);
	al_draw_filled_rectangle(20, 37, 22, 47, BLACK);			
	al_draw_filled_rectangle(27, 37, 29, 47, BLACK);
	al_set_target_bitmap(al_get_backbuffer(resources.display));

	//checkpoint
	_bitmaps.checkpoint = al_create_bitmap(tile_size, tile_size);
	if(!_bitmaps.checkpoint) {
      fprintf(stderr, "failed to create checkpoint bitmap!\n");
      return DISPLAY_ERROR;
	}

	al_set_target_bitmap(_bitmaps.checkpoint);
	al_clear_to_color(al_map_rgb(255, 204, 51));
	al_draw_filled_triangle(20, 0, 50, 15, 20, 25, YELLOW);
	al_draw_line(20, 0, 20, 50, YELLOW, 3);
	al_draw_filled_rectangle(12.5, 42.5, 27.5, 50, YELLOW);
	al_set_target_bitmap(al_get_backbuffer(resources.display));

	//rock
	_bitmaps.rock = al_create_bitmap(tile_size, tile_size);
	if(!_bitmaps.rock) {
      fprintf(stderr, "failed to create rock bitmap!\n");
      return DISPLAY_ERROR;
	}

	al_set_target_bitmap(_bitmaps.rock);
	al_clear_to_color(al_map_rgb(255, 204, 51));
	al_draw_filled_ellipse(19, 25, 7, 16, al_map_rgb(139, 69, 19));
	al_draw_filled_ellipse(16, 24, 2.5, 14, al_map_rgb(0, 100, 0));
	al_draw_filled_ellipse(32, 25, 12, 22, al_map_rgb(139, 69, 19));
	al_draw_filled_ellipse(30, 23, 8, 18, al_map_rgb(0, 100, 0));
	al_draw_filled_ellipse(33, 25, 5, 20, al_map_rgb(139, 69, 19));
	al_draw_filled_ellipse(25, 34, 22, 8, al_map_rgb(139, 69, 19));
	al_draw_filled_ellipse(29, 39, 14, 8, al_map_rgb(139, 69, 19));
	al_draw_filled_circle(8, 45, 3, al_map_rgb(139, 69, 19));
	al_draw_filled_circle(45, 47, 5, al_map_rgb(139, 69, 19));
	al_draw_filled_circle(46, 12, 3.5, al_map_rgb(139, 69, 19));
	al_draw_filled_circle(43, 4, 5, al_map_rgb(139, 69, 19));
	al_set_target_bitmap(al_get_backbuffer(resources.display));

	//Where Merelda put stuff in!!!!!///////////////////////////////////////////
	//Where Merelda put stuff in!!!!!///////////////////////////////////////////
	//Where Merelda put stuff in!!!!!///////////////////////////////////////////
	//Where Merelda put stuff in!!!!!///////////////////////////////////////////
	//Where Merelda put stuff in!!!!!///////////////////////////////////////////
	//Where Merelda put stuff in!!!!!///////////////////////////////////////////

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

