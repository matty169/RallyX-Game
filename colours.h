/** colours.h Defines colours for use in Allegro  
  * \author SP Levitt
  * \version 2.0
  * \date 2011-08-05
  */

#ifndef COLOURS_H
#define COLOURS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>

// A number of colour definitions have been created here to make the code more readable - 
// add your own as required, and include where necessary.

const ALLEGRO_COLOR RED = al_color_name("red");
const ALLEGRO_COLOR BLUE = al_color_name("mediumblue");
const ALLEGRO_COLOR GREEN = al_color_name("green");
const ALLEGRO_COLOR YELLOW = al_color_name("yellow");
const ALLEGRO_COLOR TURQUOISE = al_color_name("mediumturquoise");
const ALLEGRO_COLOR VIOLET = al_color_name("violet");
const ALLEGRO_COLOR BLACK = al_color_name("black");
const ALLEGRO_COLOR WHITE = al_color_name("white");

// Note al_color_name recognises the colour names found here:
// http://www.w3.org/TR/2010/PR-css3-color-20101028/#svg-color

#endif
