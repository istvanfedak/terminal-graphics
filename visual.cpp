#include "visual.hpp"

WINDOW * cw_ = NULL;   // current window
int wantc_   = 2;      // want color
int winc_    = 1;      //window color
bool winb_   = false;  //window box
string whd   = "west"; //window heading degrees 


// sets a pen color to an rgb value
int set_pen_color_int(int r, int g, int b)
{ // check if your can change the terminals color
  if( !can_change_color() )
    // check if the standard window is NULL
    if(stdscr != NULL)
      // print error
      mvwprintw(stdscr,1,1,"Terminal has no RGB support");
  // set pen color
  init_color(color::rgb,r,g,b);
  return color::rgb; }

// this function is depreciated and needs to be updated
// TODO update function
int set_pen_color(int foreground, int background)
{ wantc_++; //This allows 256 choices
  if(wantc_ >=1000)
  { mvwprintw(stdscr,1,1,"Out of colors, learn about color pair indexs in ncurses");
    return 0; }
  init_pair(wantc_, foreground, background);
  wattron(cw_,COLOR_PAIR(wantc_));
  return wantc_; }

// set a pen color to a created color pair
void set_pen_color(const int index)
{ if(index ==-1)
    wattron(cw_,COLOR_PAIR(winc_));
  else
    wattron(cw_, COLOR_PAIR(index)); }

// free a pen color
void unset_pen_color(const int index)
{ wattroff(cw_, COLOR_PAIR(index)); }

// set window color
void set_window_color(int foreground, int background)
{ init_pair(winc_, foreground, background);
  wrefresh(cw_); }

void make_window(int drawBox)
{ winb_ = drawBox;
  if(stdscr == NULL)
    initscr();
  // allow to exit the profram
  cbreak();
  if(cw_ != NULL) delwin(cw_);
    cw_ = stdscr;
  if(!has_colors())
    mvwprintw(stdscr,1,1,"Terminal has no Colors");
  else
    start_color();
  if(drawBox)
    box(cw_,0,0); // makes a box around window

  init_pair(winc_,COLOR_WHITE,COLOR_BLACK);
  wbkgd(cw_,COLOR_PAIR(winc_));
  wrefresh(cw_);
  curs_set(0); }

void make_window(int width, int height, int x, int y, int drawBox)
{ winb_ = true;
  //initializes the screen
  // sets up memory and clears the screen
  if(stdscr == NULL)
    initscr();
  // allow to exit program
  cbreak();
  // getting terminal size
  int xb,yb,xm,ym;
  getbegyx(stdscr,yb,xb);
  getmaxyx(stdscr,ym,xm);

  // makes a window
  if(cw_ != NULL)
    delwin(cw_);
  if(x==-7777||y==-7777)
    cw_ = newwin(height,width,(ym-yb)/2-height/2,(xm-xb)/2-width/2);
  else
    cw_ = newwin(height,width,y,x);

  if(!has_colors())
    mvwprintw(stdscr,1,1,"Terminal has no Colors");
  else start_color();
  if(drawBox)
    box(cw_,0,0); // makes a box around window

  init_pair(winc_,COLOR_WHITE,COLOR_BLACK);
  wbkgd(cw_,COLOR_PAIR(winc_));
  wrefresh(cw_); // refreshes the window
  curs_set(0); }

// delete window
void destroy_window()
{ // deallocates memory and ends ncureses
  if(cw_ !=NULL)
    delwin(cw_);
  endwin(); }

// refresh window
void refresh_window()
{ // refreshes the screen to match whats in memory
  if(cw_ == stdscr)
    refresh();
  else
    wrefresh(cw_); }

void set_window_position(int x, int y)
{ mvwin(cw_, y,x);
  refresh();
  wrefresh(cw_); }

void set_window_size(int w, int h)
{ wresize(cw_,h,w);
  if(winb_)
    //for some reason color wont change
    box(cw_,0,0);

  // TODO optimize refresh
  refresh();
  wrefresh(cw_); }

// clear contents of window
void clear_window()
{ // clear(); same as library.h
  wclear(cw_); }

// get the x & y position of the window
void get_position(int & x, int & y)
{ getyx(cw_,y,x); }

int get_x_position()
{ int x, y;
  getyx(cw_, y, x);
  return x; }

int get_y_position()
{ int x,y;
  getyx(cw_,y,x);
  return y; }

int get_window_width()
{ int xb,yb,xm,ym;
  getbegyx(cw_,yb,xb);
  getmaxyx(cw_,ym,xm);
  return xm-xb; }

int get_window_height()
{ int xb,yb,xm,ym;
  getbegyx(cw_,yb,xb);
  getmaxyx(cw_,ym,xm);
  return ym-yb; }

void get_window_size(int &w, int &h)
{ int xb,yb,xm,ym;
  getbegyx(cw_,yb,xb);
  getmaxyx(cw_,ym,xm);
  w = xm-xb;
  h = ym-yb; }

int get_screen_width()
{ int xb,yb,xm,ym;
  getbegyx(stdscr,yb,xb);
  getmaxyx(stdscr,ym,xm);
  return xm-xb; }

int get_screen_height()
{ int xb,yb,xm,ym;
  getbegyx(stdscr,yb,xb);
  getmaxyx(stdscr,ym,xm);
  return ym-yb; }

void get_screen_size(int &w, int &h)
{ int xb,yb,xm,ym;
  getbegyx(stdscr,yb,xb);
  getmaxyx(stdscr,ym,xm);
  w = xm-xb;
  h = ym-yb; }

void move_to(int x, int y)
{ wmove(cw_,y,x); }

void wait(double d)
{ wtimeout(cw_,(int)(d*1000)); }

int wait_for_key_typed(double d){
	noecho();
	wait(d);
	char c = wgetch(cw_);
	echo();
	return (int)c;
}

char read_char(){
	return wgetch(cw_);
}

string read_string(){
  char i;
  string str = "";
  while(true)
  { i = wgetch(cw_);
    if(i == '\n')
      break;
    else if(i== (char)127)
    { int x, y;
      getyx(cw_,y,x);
      if(str.length()>0)
      { wmove(cw_,y,x-3); //moves to errase
        wprintw(cw_,"   "); // erases
        wmove(cw_,y,x-3); //moves to original position
        wrefresh(cw_); }
      else
      { wmove(cw_,y,x-2); //moves to errase
        wprintw(cw_,"  "); // erases
        wmove(cw_,y,x-2); //moves to original position
        wrefresh(cw_); }
      str = str.substr(0, str.length()-1); }
    else str+= i; }
  return str; }


int read_int()
{ return atoi((read_string()).c_str()); }

double read_double()
{ return atof((read_string()).c_str()); }

void write_string(string s)
{ //write_string(s,whd);
  wprintw(cw_,s.c_str()); }

void write_string(string s, const string dir)
{ int x, y;
  getyx(cw_,y,x);
  if(dir == direction::center)
  { wmove(cw_, y ,x-s.length()/2);
    wprintw(cw_,s.c_str()); }

  if(dir == direction::north)
  { for(int i = 0; i< s.length();i++)
    { wmove(cw_, y-i,x);
      wprintw(cw_,"%c",s[i]); } }

  if(dir == direction::north_east)
  { for(int i = 0; i< s.length();i++)
    { wmove(cw_, y-i,x+2*i);
      wprintw(cw_,"%c",s[i]); } }

  if(dir == direction::east)
  { wprintw(cw_,s.c_str()); }

  if(dir == direction::south_east)
  { for(int i = 0; i< s.length();i++)
    { wmove(cw_, y+i,x+2*i);
      wprintw(cw_,"%c",s[i]); } }

  if(dir == direction::south)
  { for(int i = 0; i< s.length();i++)
    { wmove(cw_, y+i,x);
      wprintw(cw_,"%c",s[i]); } }

  if(dir == direction::south_west)
  { for(int i = 0; i< s.length();i++)
    { wmove(cw_, y+i,x-2*i);
      wprintw(cw_,"%c",s[i]); } }

  if(dir == direction::west)
  { wmove(cw_, y,x-s.length());
    wprintw(cw_,s.c_str());
    wmove(cw_, y,x-s.length()); }

  if(dir == direction::north_west)
  { for(int i = 0; i< s.length();i++)
    { wmove(cw_, y-i,x-2*i);
      wprintw(cw_,"%c",s[i]); } } }

void write_string(string s, int x, int y)
{ mvwprintw(cw_,y,x,s.c_str()); }

void write_char(char c)
{ wprintw(cw_,"%c",c);
  wrefresh(cw_); }

void write_int(int i)
{ wprintw(cw_,"%d",i);
  wrefresh(cw_); }

void write_double(double d)
{ wprintw(cw_, "%f",d);
  wrefresh(cw_); }

void write_bool(bool b)
{ wprintw(cw_, "%d",b);
  wrefresh(cw_); }

void set_heading_degrees(const string s)
{ whd = s; }

void draw_distance(int i)
{ char c;
  if(whd == direction::north || whd == direction::south) c = '|';
  if(whd == direction::east || whd == direction::west) c = '_';
  if(whd == direction::north_east || whd == direction::south_west) c ='/';
  if(whd == direction::north_west || whd == direction::south_east) c = (char)92;

  string s(i,c);
  write_string(s,whd); }

void draw_rectangle(int x, int y, int w, int h)
{ move_to(x+1,y);
  set_heading_degrees(direction::east);
  draw_distance(w-1);
  move_to(x+w,y+1);
  set_heading_degrees(direction::south);
  draw_distance(h);


  move_to(x+w,y+h);
  set_heading_degrees(direction::west);
  draw_distance(w);
  set_heading_degrees(direction::north);
  draw_distance(h); }

void fill_rectangle(int x, int y, int w, int h)
{ for(int i=0; i<w; i++)
  { for(int j=0; j<h; j++)
    { mvwprintw(cw_,y+j,x+i," "); } } }

void draw_star(const int x, const int y, const int len)
{ move_to(x,y);
  set_heading_degrees(direction::north);
  draw_distance(len);
  move_to(x,y);
  set_heading_degrees(direction::north_east);
  draw_distance(len);
  move_to(x,y);
  set_heading_degrees(direction::east);
  draw_distance(len*2);
  move_to(x,y);
  set_heading_degrees(direction::south_east);
  draw_distance(len);
  move_to(x,y);
  set_heading_degrees(direction::south);
  draw_distance(len);
  move_to(x,y);
  set_heading_degrees(direction::south_west);
  draw_distance(len);
  move_to(x,y);
  set_heading_degrees(direction::west);
  draw_distance(len*2);
  move_to(x,y);
  set_heading_degrees(direction::north_west);
  draw_distance(len); }

/*
 TODO fix box color when window is moved
 when using set_window_size() and set_window_position() together the old border never goes away
*/

//###################### library.h unix ###########################
int get_clock_time()
{ time_t t;
  time(&t);
  struct tm * lt = localtime(&t);
  return lt->tm_hour*10000 + lt->tm_min*100 + lt->tm_sec; }

int get_calendar_date()
{ time_t t;
  time(&t);
  struct tm * lt = localtime(&t);
  return (lt->tm_year+1900)*10000 + (lt->tm_mon+1)*100 + lt->tm_mday; }

void print(string s)
{ printf("%s", s.c_str()); }

void print(const char * s)
{ printf("%s", s); }

void print(int n)
{ printf("%d", n); }

void print(char c)
{ printf("%c", c); }

void print(double d)
{ printf("%g", d); }

void print(bool b)
{ if (b)
    printf("true");
  else
    printf("false"); }

void print_string(string s)
{ printf("%s", s.c_str()); }

void print_int(int n)
{ printf("%d", n); }

void print_char(char c)
{ printf("%c", c); }

void print_double(double d)
{ printf("%g", d); }

void print_float(double d)
{ print_double(d); }

void print_hexadecimal(int n)
{ printf("%9X", n); }

void print_binary(int n)
{ bool something=false;
  unsigned int m=0x80000000;
  for (int i=0; i<32; i+=1)
  { if (n&m)
    { printf("1");
      something=true; }
    else if (something)
      printf("0");
    m>>=1; }
  if (!something)
    printf("0"); }

void print_bool(bool b)
{ if (b)
    printf("true");
  else
    printf("false"); }

void new_line()
{ printf("\n"); }

/*
string _x_readsomething()
{ string r="";
  int c=0;
  while (true)
  { c=getc(stdin);
    if (c==EOF || c>' ' && c!=',')
      break; }
  while (true)
  { if (c<=' ' || c==',')
      break;
    r+=(char)c;
    c=getc(stdin); }
  ungetc(c, stdin);
  return r; }

string read_string()
{ return _x_readsomething(); }

string read_line()
{ string r="";
  while (true)
  { int c = getc(stdin);
    if (c=='\n' || c==EOF)
      break;
    r+=(char)c; }
  return r; }

int read_int()
{ string s=_x_readsomething();
  char * stopper;
  int val = strtol(s.c_str(), &stopper, 10);
  if (*stopper!=0)
  { cerr << "\n'" << s << "' is not an int value\n";
    exit(1); }
  return val; }

double read_double()
{ string s=_x_readsomething();
  char * stopper;
  double val = strtod(s.c_str(), &stopper);
  if (*stopper!=0)
  { cerr << "\n'" << s << "' is not a double value\n";
    exit(1); }
  return val; }

double read_float()
{ string s=_x_readsomething();
  char * stopper;
  double val = strtod(s.c_str(), &stopper);
  if (*stopper!=0)
  { cerr << "\n'" << s << "' is not a float value\n";
    exit(1); }
  return val; }

bool _x_same(string s, const char * t)
{ return strcasecmp(s.c_str(), t)==0; }

bool read_bool()
{ string s=_x_readsomething();
  if (s=="1") return true;
  if (s=="0") return false;
  if (_x_same(s, "true")) return true;
  if (_x_same(s, "false")) return false;
  if (_x_same(s, "yes")) return true;
  if (_x_same(s, "no")) return false;
  if (_x_same(s, "t")) return true;
  if (_x_same(s, "f")) return false;
  if (_x_same(s, "y")) return true;
  if (_x_same(s, "n")) return false;
  cerr << "\n'" << s << "' is not a bool value.\n";
  exit(1);
  return false; }
*/

int init_random()
{ srandom(time(NULL));
  return 0; }

void not_really_random(int n)
{ srandom(n); }

int random_in_range(int a, int b)
{ if (b<a)
    return random()%(a-b+1)+b;
  else
    return random()%(b-a+1)+a; }

void exit()
{ exit(0); }

double get_cpu_time()
{ struct rusage ruse;
  getrusage(RUSAGE_SELF, &ruse);
  return ruse.ru_utime.tv_sec+ruse.ru_utime.tv_usec/1000000.0 + 
         ruse.ru_stime.tv_sec+ruse.ru_stime.tv_usec/1000000.0; }

//#################################################################

