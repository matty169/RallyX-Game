#include "Checkpoint.h"
#include <iostream>
using namespace std;

const int tile_size = 50;

Checkpoint::Checkpoint(const Coordinate pos_x, const Coordinate pos_y): _pos_x(pos_x), _pos_y(pos_y)
{
	//throws an exception when no coordinate passed in is (0,0)
	if (_pos_x < 0 || _pos_y < 0) throw UndefinedCheckpoint();

	cout << "_pos_x: " << _pos_x << ", _pos_y: " << _pos_y << endl;
}

Coordinate Checkpoint::get_x() const
{
	return _pos_x;
}

Coordinate Checkpoint::get_y() const
{
	return _pos_y;
}

//void UndefinedCheckpoint::errorMessage()
//{
//	al_show_native_message_box(NULL, NULL, NULL, "Fail to create checkpoint", NULL, ALLEGRO_MESSAGEBOX_ERROR);
//}