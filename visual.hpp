/*****************************************************************************
 *  Compilation:  none
 *  Execution:    none
 *  Dependencies: ncurses
 *
 *  library.h like graphics programing library. This library provides a basic
 *  capability for creating a ui with your terminal programs. It uses the
 *  ncurses programing library.
 *
 ******************************************************************************/

#include <ncurses.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <sys/resource.h>

using namespace std;

/*
###############################################################################
Instructions on how to use:
- download the file to the current working directory
- create a makefile file
- withing the makefile type the following:

all: executable_file_name

main: source_file_name.cpp
        g++ source_file_name.cpp -o executable_file_name -lncurses visual.h

- make sure that the space after g++ is a tab
- to compile type make in the terminal
- enjoy!

###############################################################################

stdscr - standard screen where program runs

cbreak(); // allows command breaks
raw(); allows no command breaks
noecho(); user input wont be shown
eco(); user unput will be shown
wborder(win, left, right, top, bottom, tlc,trc,blc,brc);
	- allows better border customization (tlc = top left corner)
attributes:
attron(); sets an attribute
attroff(); removes an attribute

list of atributes:

	A_NORMAL
	A_STANDOUT
	A_REVERSE
	A_BLINK
	A_DIM
	A_BOLD
	A_PROTECT
	A_INVIS
	A_ALTCHARSET
	A_CHARTEXT

colors:
has_colors() returns a bool telling you if terminal has color
start_color(); sets up colors for terminal
- color pairs are a pair of a forground and background color
init_pair(pair id int, foreground, background);
- to use  attron(COLOR_PAIR(ID));

list of colors:

	COLOR_PAIR(n)
	COLOR_BLACK	0
	COLOR_RED	1
	COLOR_GREEN	2
	COLOR_YELLOW	3
	COLOR_BLUE	4
	COLOR_MAGENTA	5
	COLOR_CYAN	6
	COLOR_WHITE	7

Supporting RGB
init_color(COLOR_CYAN,0-999,0-999,0-999); sets COLOR_CYAN to a new color
can_change_color() returns a bool that tells you if you can change color

arrow keys:
keypad(WINDOW * win,true); - makes it so that you can use arrow keys

KEY_UP
KEY_DOWN

*/

namespace color
{ const int

    black = 0, // COLOR_BLACK
      red = 1, // COLOR_RED
    green = 2, // COLOR_GREEN
   yellow = 3, // COLOR_YELLOW
     blue = 4, // COLOR_BLUE
  magenta = 5, // COLOR_MAGENTA
     cyan = 6, // COLOR_CYAN
    white = 7, // COLOR_WHITE
     rgb = 8;  // unkown
}

namespace direction
{ const string

       north = "north",
  north_west = "north_west",
        west = "west",
  south_west = "south_west",
       south = "south",
  south_east = "south_east",
        east = "east",
  north_east = "north-east",
      center = "center";
}

// sets a pen color to an rgb value
int set_pen_color_int(int r, int g, int b);

// this function is depreciated and needs to be updated
// TODO update function
int set_pen_color(int foreground, int background);

// set a pen color to a created color pair
void set_pen_color(const int index= -1);

// free a pen color
void unset_pen_color(const int index);

// set window color
void set_window_color(int foreground, int background);

void make_window(int drawBox = 1);

void make_window(int width, int height, int x = -7777, int y = -7777, int drawBox = 1);

// delete window
void destroy_window();

// refresh window
void refresh_window();

void set_window_position(int x, int y);

void set_window_size(int w, int h);

// clear contents of window
void clear_window();

// get the x & y position of the window
void get_position(int & x, int & y);

int get_x_position();

int get_y_position();

int get_window_width();

int get_window_height();

void get_window_size(int &w, int &h);

int get_screen_width();

int get_screen_height();

void get_screen_size(int &w, int &h);

void move_to(int x, int y);

void wait(double d = -1);

int wait_for_key_typed(double d =-1);

char read_char();

string read_string();

int read_int();

double read_double();

void write_string(string s);

void write_string(string s, const string dir);

void write_string(string s, int x, int y);

void write_char(char c);

void write_int(int i);

void write_double(double d);

void write_bool(bool b);

void set_heading_degrees(const string s);

void draw_distance(int i);
void draw_rectangle(int x, int y, int w, int h);

void fill_rectangle(int x, int y, int w, int h);

void draw_star(const int x, const int y, const int len);

/*
 TODO fix box color when window is moved
 when using set_window_size() and set_window_position() together the old border never goes away
*/

//###################### library.h unix ###########################
int get_clock_time();

int get_calendar_date();

void print(string s);

void print(const char * s);

void print(int n);

void print(char c);

void print(double d);

void print(bool b);

void print_string(string s);

void print_int(int n);

void print_char(char c);

void print_double(double d);

void print_float(double d);

void print_hexadecimal(int n);

void print_binary(int n);

void print_bool(bool b);

void new_line();

int init_random();

const int _x_pointless = init_random();

void not_really_random(int n=1289);

int random_in_range(int a, int b);

void exit();

double get_cpu_time();

//#################################################################
