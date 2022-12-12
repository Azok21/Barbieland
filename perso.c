#include <ncurses.h>
#include "structure.h"

void Afficher_Perso(int x,int y,WINDOW *win){
	wattron(win,COLOR_PAIR(2));
	mvwprintw(win,y,x,"@");
	wattroff(win,COLOR_PAIR(2));

	wrefresh(win);
}


void Afficher_Vie(int Vie){
	WINDOW *vie = newwin(3,30,LINES-3,0);
	box(vie,0,0);

	mvwprintw(vie,1,3,"Vie :");

	for (int i = 0; i<(Vie*2); i+=2){
		wattron(vie,COLOR_PAIR(4));
		mvwprintw(vie,1,10+i,"#");
		wattroff(vie,COLOR_PAIR(4));
		mvwprintw(vie,1,11+i," ");
	}

	wrefresh(vie);
}
