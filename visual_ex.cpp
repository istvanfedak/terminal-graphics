/*****************************************************************************
 *  Compilation:  g++ star.cpp -o star -lncurses visual.h
 *  Execution:    star
 *  Dependencies: visual.h ncurses
 *
 *  Draws a star sorounded by a rectangle and asks user's name
 *
 ******************************************************************************/

#include "visual.h"

int main(){
        make_window(80,40);
        set_window_color(color::red,color::white);

        set_pen_color(color::blue, color::blue);
        fill_rectangle(22,12,36,18);
        set_pen_color(color::magenta,color::white);
        draw_star(40,20,8);
        set_pen_color(color::cyan, color::white);
        draw_rectangle(20,10,40,20);

        set_pen_color(color::green,color::white);
        move_to(2,1);
        write_string("Enter your name: ");
        string s = read_string();
        move_to(2,2);
        write_string("Hello " + s + "!");
        move_to(2,3);
        set_pen_color(color::red,color::white);
        write_string("Type anything to quit.");
        wait_for_key_typed();

        destroy_window();
        return 0;
}

