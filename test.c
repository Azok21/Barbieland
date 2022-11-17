#include <ncurses.h>

int main(){

	initscr();
	start_color();
	noecho();
	cbreak();
	curs_set(FALSE);
	init_pair(1,COLOR_RED,COLOR_RED);

	int Vie = 7;

	WINDOW *vie = newwin(3,30,LINES-3,0);
	refresh();

	box(vie,0,0);

	mvwprintw(vie,1,3,"Vie :");

	for (int i = 0; i<(2*Vie) ;i+=2){
		wattron(vie,COLOR_PAIR(1));
		mvwprintw(vie,1,10+i,"#");
		wattroff(vie,COLOR_PAIR(1));
		mvwprintw(vie,1,11+i," ");
	}

	wrefresh(vie);

	getch();
	endwin();
	return 0;

}
