#include "visual.h"
#include <iostream>
#include <fstream>

struct maze{
	int ixA,iyA;
	int xA,yA;
	int ixE,iyE;
	int xE, yE;
	int ixB, iyB;
	int xB, yB;
	int xM, yM;
	bool back;
	int wall, space, treasure, enemy, alien, normal, selected;
	maze(){
		xA = -1, yA = -1;
		ixA = -1, iyA = -1;
		xE = -1, yE = -1;
		ixE = -1, iyE = -1;
		xB = -1, yB = -1;
		ixB = -1, iyB = -1;
		
		back = false;
		wall = set_pen_color(color::black,color::black);
		space = set_pen_color(color::white,color::white);
		treasure = set_pen_color(color::yellow,color::yellow);
		enemy = set_pen_color(color::red,color::red);
		alien = set_pen_color(color::green,color::green);
		normal = set_pen_color(color::black,color::white);
		selected = set_pen_color(color::white,color::black);
	}	
	void setA(int x, int y){
		xA = x;
		yA = y;
	}
	void setE(int x, int y){
                xE = x;
                yE = y;
        }
	void setB(int x, int y){
                xB = x;
                yB = y;
        }
	bool checkE(int x, int y){ 
		if(x == xE && y == yE) return true;
		else return false;
	}
	bool checkB(int x, int y){
		if(x == xB && y == yB) return true;
		else return false;
	}
};

int read_size(ifstream & in){
	string line;
	int line_count=0;
	while(true){
		getline(in,line);
		if(in.fail()) break;
		line_count++;
	}
	in.clear();
	in.seekg(0,ios::beg);		
	return line_count;
}

void read_file(ifstream & in, string arr[], const int size){
	string line;
	for(int i =0; i<size; i++){
		getline(in,line);
		if(in.fail())break;
		arr[i] = line;
	}
}

void print(string arr[], const int size){
	for(int i = 0; i<size; i++)
		cout<<arr[i]<<endl;
}

void fill_maze(string arr[], maze &game){
	for(int i = 0; i<game.yM; i++){
		for(int j =0; j< game.xM; j++){
			if((int)arr[i][j] == (int)'A'){
				game.ixA = j;
				game.iyA = i;
				game.setA(j+1,i+1);
				set_pen_color(game.alien);
				move_to(j+1,i+1);
				write_char('@');
			}
			else if(arr[i][j] == 'E'){
				arr[i][j] = '.';
				game.ixE = j;
                                game.iyE = i;
				game.setE(j+1,i+1);
				set_pen_color(game.enemy);
                                move_to(j+1,i+1);
                                write_char('*');
			}
			else if(arr[i][j] == 'B'){
				arr[i][j] = '.';
				game.ixB = j;
                                game.iyB = i;
				game.setB(j+1,i+1);
				set_pen_color(game.treasure);
                                move_to(j+1,i+1);
                                write_char('$');
			}
			else if(arr[i][j] == '.'||arr[i][j] == 'l'||arr[i][j] == 'r'||arr[i][j] == 'u'||arr[i][j] == 'd'){
				arr[i][j] = '.';
				set_pen_color(game.space);
                                move_to(j+1,i+1);
                                write_char(' ');
			}
			else{
				set_pen_color(game.wall);
                                move_to(j+1,i+1);
                                write_char('#');
			}
		}
	}	
}

void print_coor(int x, int y){
	set_pen_color(color::black,color::white);
	move_to(1,1);
        write_int(x);
        move_to(3,1);
        write_int(y);
}
void back(string arr[], int c, maze &game){
	if(arr[game.yA-1][game.xA-1]!='.') return;
	else if(c == 'l') arr[game.yA-1][game.xA-1] = 'r';
	else if(c == 'r') arr[game.yA-1][game.xA-1] = 'l';
	else if(c == 'u') arr[game.yA-1][game.xA-1] = 'd';
	else if(c == 'd') arr[game.yA-1][game.xA-1] = 'u';
}
void move_alien(string arr[], maze &game, int c,bool brick_road = false){
	if (c == (int)'l'|| c== 68){
        /* make the robot move one square to the left */
        	if(game.xA>1&& arr[game.yA-1][game.xA-2] !='@'){
        		move_to(game.xA,game.yA);
                	if(!brick_road) set_pen_color(game.space);
			else set_pen_color(game.treasure);
                	write_char(' ');
			game.xA--;
			back(arr,'l',game);
			move_to(game.xA,game.yA);
                	if(!brick_road) set_pen_color(game.alien);
			else set_pen_color(game.treasure);
			write_char('@');
                }
        }
	else if (c == (int)'r'||c == 67){
        /* make the robot move one square to the right */
        	if(game.xA<game.xM && arr[game.yA-1][game.xA] !='@'){
               		move_to(game.xA,game.yA);
                        if(!brick_road) set_pen_color(game.space);
			else set_pen_color(game.treasure);
                        write_char(' ');
                        game.xA++;
			back(arr,'r',game);
                        move_to(game.xA,game.yA);
                        if(!brick_road) set_pen_color(game.alien);
			else set_pen_color(game.treasure);
                        write_char('@');
                }
       	}
        else if (c == (int)'u'||c == 65){
        /* make the robot move one square up */
         	if(game.yA>1 && arr[game.yA-2][game.xA-1] !='@'){
                	move_to(game.xA,game.yA);
                        if(!brick_road) set_pen_color(game.space);
			else set_pen_color(game.treasure);
                        write_char(' ');
			game.yA--;
			back(arr,'u',game);
                        move_to(game.xA,game.yA);
                        if(!brick_road) set_pen_color(game.alien);
			else set_pen_color(game.treasure);
                        write_char('@');
        	}
        }
	else if (c == (int)'d'||c== 66){
        /* make the robot move one square down */
        	if(game.yA<game.yM && arr[game.yA][game.xA-1] !='@'){
                	move_to(game.xA,game.yA);
                        if(!brick_road) set_pen_color(game.space);
			else set_pen_color(game.treasure);
                        write_char(' ');
                        game.yA++;
			back(arr,'d',game);
                        move_to(game.xA,game.yA);
                        if(!brick_road) set_pen_color(game.alien);
			else set_pen_color(game.treasure);
                        write_char('@');
                }
	}
}
char can_do(string arr[],maze &game){
	int x = game.xA - game.xE;
	int y = game.yA - game.yE;
	int xAbso;
	int yAbso;
	if(x<0) xAbso = x* -1;
	else xAbso = x;
	if(y<0) yAbso = y* -1;	
	else yAbso = y;
	if(xAbso>yAbso){
		if(x<0){
			if(arr[game.yE-1][game.xE-2]!= '@')
				return 'l';
			else{
				if(y<0){
                			if(arr[game.yE-2][game.xE-1]!= '@')
                				return 'u';
        			}
        			else return 'd';
        		}
		}
		else{
			if(arr[game.yE-1][game.xE]!= '@')
				return 'r';
			else{
                                if(y<0){
                                        if(arr[game.yE-2][game.xE-1]!= '@')
                                                return 'u';
                                }
                                else{
					return 'd';
				}
                        }
		}
	}
	if(y<0){
		if(arr[game.yE-2][game.xE-1]!= '@')
			return 'u';
		else{
                        if(x<0){
                        	if(arr[game.yE-1][game.xE-2]!= '@')
                                                return 'l';
                        }
                        else return 'r';
                }
	}
	else{	
		if(arr[game.yE][game.xE-1]!= '@')
			return 'd';
		else{
                        if(x<0){
                                if(arr[game.yE-1][game.xE-2]!= '@')
                                                return 'l';
                        }
                        else return 'r';
                }
	}
	return 'r';
}
void move_enemy(string arr[], maze &game){
	int c = can_do(arr,game); //random_in_range(65,68);
	if (c == (int)'l'|| c== 68){
        /* make the robot move one square to the left */
                if(game.xE>1&& arr[game.yE-1][game.xE-2] !='@'){
                        move_to(game.xE,game.yE);
                        set_pen_color(game.space);
                        write_char(' ');
                        game.xE--;
                        move_to(game.xE,game.yE);
                        set_pen_color(game.enemy);
                        write_char('@');
                }
        }
        else if (c == (int)'r'||c == 67){
        /* make the robot move one square to the right */
                if(game.xE<game.xM && arr[game.yE-1][game.xE] !='@'){
                        move_to(game.xE,game.yE);
                        set_pen_color(game.space);
                        write_char(' ');
                        game.xE++;
                        move_to(game.xE,game.yE);
                        set_pen_color(game.enemy);
                        write_char('@');
                }
        }
        else if (c == (int)'u'||c == 65){
        /* make the robot move one square up */
                if(game.yE>1 && arr[game.yE-2][game.xE-1] !='@'){
                        move_to(game.xE,game.yE);
                        set_pen_color(game.space);
                        write_char(' ');
                        game.yE--;
                        move_to(game.xE,game.yE);
                        set_pen_color(game.enemy);
                        write_char('@');
                }
        }
	else if (c == (int)'d'||c== 66){
        /* make the robot move one square down */
                if(game.yE<game.yM && arr[game.yE][game.xE-1] !='@'){
                        move_to(game.xE,game.yE);
                        set_pen_color(game.space);
                        write_char(' ');
                        game.yE++;
                        move_to(game.xE,game.yE);
                        set_pen_color(game.enemy);
                        write_char('@');
                }
        }
}
void brick_road(string arr[], maze &game){
	while(arr[game.yA-1][game.xA-1] != 'A'){
		move_alien(arr,game,arr[game.yA-1][game.xA-1],true);		
	}
}
int end_check(string arr[],maze &game){
	if(game.xA == game.xB && game.yA == game.yB){
                set_pen_color(color::black, color::yellow);
                move_to(game.xA,game.yA);
                write_char('$');
                set_window_color(color::black,color::green);
                set_pen_color(color::green, color::white);
                move_to(1,1);
                write_string("You won!");
		brick_road(arr,game);		
		char c;
		while(true){
                	c =wait_for_key_typed();
			if(c == 'q' || c == '\n'){
				set_window_color(color::white,color::black);
				break;
			}
		}
		set_window_color(color::black,color::white);
		return 'q';
        }
        else if(game.xA == game.xE && game.yA == game.yE){
                set_pen_color(color::black, color::red);
                move_to(game.xE,game.yE);
                write_char('X');
                set_window_color(color::black,color::red);
                set_pen_color(color::red, color::white);
                move_to(1,1);
                write_string("You lost.");
                char c;
                while(true){
                        c =wait_for_key_typed();
                        if(c == 'q'|| c == '\n'){
				set_window_color(color::white,color::black);
				break;
			}
                }
		set_window_color(color::black,color::white);
		return 'q';
	}
	return 0;
}

int auto_mode(string arr[], maze & game){
	if(game.xA>1 && (arr[game.yA-1][game.xA-2] == '.' || game.checkE(game.xA-1,game.yA)||game.checkB(game.xA-1,game.yA))) 
		return 'l';
	else if(game.xA<game.xM && (arr[game.yA-1][game.xA] == '.' ||  game.checkE(game.xA+1,game.yA)||game.checkB(game.xA+1,game.yA))) 
		return 'r';
	else if(game.yA>1 && (arr[game.yA-2][game.xA-1] == '.' ||  game.checkE(game.xA,game.yA-1)||game.checkB(game.xA,game.yA-1))) 
		return 'u';
	else if(game.yA<game.yM && (arr[game.yA][game.xA-1] == '.' ||  game.checkE(game.xA,game.yA+1)||game.checkB(game.xA,game.yA+1)))
		return 'd';
 	if(end_check(arr,game)=='q') return 'q'; //interesting event;
	return arr[game.yA-1][game.xA-1]; //back
}

void the_game(string arr[], maze &game){
	fill_maze(arr,game);
	bool Auto = false;
        while(true){
                int c = wait_for_key_typed(0.18);
                if(Auto && c !=(int)'a') c = auto_mode(arr,game);
                else if (c == 'q'){
                        break;
                }
                else if(c == 'a'){
                        if(Auto) Auto= false;
                        else Auto = true;
                }
                else if(c == 'b'){
                        c = arr[game.yA-1][game.xA-1];
                }
                move_alien(arr, game, c);
                if(c == ERR) move_enemy(arr, game);
                if(end_check(arr,game)=='q') break;
        }
	arr[game.iyA][game.ixA] = 'A';
        arr[game.iyE][game.ixE] = 'E';
        arr[game.iyB][game.ixB] = 'B';
	clear_window();
}

void ui( maze &game, int i){
	move_to(game.xM/2,game.yM/2-2);
	if(i==0) set_pen_color(game.selected);
	else set_pen_color(game.normal);
	write_string("PLAY", direction::center);
	
	move_to(game.xM/2,game.yM/2);
	if(i==1) set_pen_color(game.selected);
        else set_pen_color(game.normal);
	write_string("INFO", direction::center);

	move_to(game.xM/2,game.yM/2+2);
	if(i==2) set_pen_color(game.selected);
        else set_pen_color(game.normal);
	write_string("QUIT", direction::center);
}

void info(maze &game){
	clear_window();
	set_pen_color(game.normal);
	move_to(game.xM/2,game.yM/2-4);
	write_string("q - quit", direction::center);
	set_pen_color(game.selected);
	move_to(game.xM/2,game.yM/2-2);
	write_string("u - up", direction::center);
	move_to(game.xM/2,game.yM/2);
        write_string("l - left   r - right", direction::center);
	move_to(game.xM/2,game.yM/2+2);
        write_string("d - down", direction::center);
	set_pen_color(game.normal);
	move_to(game.xM/2,game.yM/2 +4);
	write_string("b - back, a - auto", direction::center);
	move_to(game.xM/2,game.yM/2);
	write_string(" ", direction::center);
	set_pen_color(game.selected);
	move_to(game.xM/2,game.yM/2+6);
	write_string("RETURN", direction::center);
	while(true){
		int c = wait_for_key_typed();
		if(c == '\n' || c == 'q'|| c == 'r'){
		 	clear_window();
			return;
		}
	}
}



void main_menu(string arr[], maze &game){
	clear_window();
	int i = 0;
	while(true){
		ui(game,i);
		int c = wait_for_key_typed();
		if(c == '\n'){
			if(i == 0) c = 'p';
			else if(i == 1) c = 'i';
			else if(i == 2) c = 'q';
		}
		
		if(c == 'p'){
			the_game(arr,game);
		}
		else if (c == 'i'){
			info(game);
		}
		else if (c == 'q'){		
			destroy_window();
			exit(0);
		}
		else if((c == 'u' || c == 65) && i>0) i--;
		else if((c == 'd' || c == 66) && i<2) i++;
	}
}

int main(int argc, char *argv[]){
	ifstream fin;
	if(argc>1) fin.open(argv[1]);
	else fin.open("maze.txt");
	if(fin.fail()){
		cerr<<"Couldn't read the file.\nUsing default maze.\n"<<endl;
		const int size = 12;
        	string arr[size] =
        	{
                	"@@@@@@..@.@@@@@@...@@@@@.......",
                	"...@......@@..@..@..@@.@...E..@",
                	"...@...@......@@.....@........@",
                	"..@@.@@@.@@@.@@@@.@..@.@.@.@@..",
                	"@..@@..@.@@...@.@.@@...@...@..@",
                	"@@..@@.@....@.....@@@.@@.@@@.@@",
               		"@.@.@....@..@.@@@..@..@..@.@...",
                	"@.@..@.@@@@@@@@.@@@@@....@.@@..",
                	"..@........@@A.....@@@@@...@@..",
                	"....@@.@@@..@@.@.@@@...@@@.@..@",
                	"..@.@................@..@..@B.@",
                	"..@@@@@@@@@@@@@@@......@@@@@@@@"
        	};
		make_window(arr[0].length()+2, size+2); //+2 for border
        	set_window_color(color::black,color::white);
        	maze game;
		game.yM = size;
		game.xM = arr[0].length();
        	main_menu(arr,game);
	}
	const int size = read_size(fin);
	string arr[12];
	read_file(fin,arr,size);
	
	make_window(arr[0].length()+2, size+2); //+2 for border
	set_window_color(color::black,color::white);
	maze game;
	game.yM = size;
        game.xM = arr[0].length();
	
	main_menu(arr,game);
	wait_for_key_typed();
	destroy_window();
	return 0;
}
