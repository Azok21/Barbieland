#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"
#include "niveau.h"
#include "perso.h"

void Afficher_menu(){
	WINDOW *menu = newwin(LINES,COLS,0,0);
        refresh();

        box(menu,0,0);
        mvwprintw(menu,LINES/2,(COLS/2)-23,"Appuyez sur une touche pour commencer à jouer");
        wrefresh(menu);
}



void Creation_liens(){
}


void Init_Couleur(){
	init_pair(1, COLOR_WHITE,COLOR_WHITE);
	init_pair(2, COLOR_GREEN,COLOR_GREEN);
	init_pair(3, COLOR_MAGENTA,COLOR_MAGENTA);
	init_pair(4, COLOR_RED,COLOR_RED);
	init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
}



void Afficher_Portail(int x,int y,WINDOW *win){
	wattron(win, COLOR_PAIR(3));
	mvwprintw(win,y,x,"p");
	wattroff(win, COLOR_PAIR(3));

	wrefresh(win);
}


int main()
{

	initscr();
	start_color();
	Init_Couleur();
	cbreak();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);

	Afficher_menu();

	int ch;
	int Vie = 3;

	PERSO perso={10,10};

	if (ch =getch())
	{
		clear();
		refresh();

		WIN *Niveau = Creation_niveau();

		perso.level = Niveau[1].salle;
		perso.levelinfo = Niveau[1];

		Afficher_Perso(perso.x,perso.y,perso.level);
		Afficher_Portail(5,5,Niveau[0].salle);
                Afficher_Portail(5,6,Niveau[1].salle);
		//Afficher_Vie(Vie);

		while((ch=getch()) != KEY_F(1))
		{
			Afficher_Portail(5,5,Niveau[0].salle);
                        Afficher_Portail(5,6,Niveau[1].salle);
			//Afficher_Vie(Vie);

			switch(ch)
			{
				case KEY_UP: if(perso.y>1) {--perso.y;Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
				case KEY_DOWN: if(perso.y<perso.levelinfo.h-2) {++perso.y,Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
				case KEY_RIGHT: if(perso.x<perso.levelinfo.w-3) {++perso.x;Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
				case KEY_LEFT: if(perso.x>1) {--perso.x;Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
			}

			if ((perso.x==2) && (perso.level==Niveau[1].salle)){werase(Niveau[1].salle);wrefresh(Niveau[1].salle);Niveau[1].salle=Creation_salle(Niveau[1].h,Niveau[1].w,Niveau[1].starty,Niveau[1].startx);
										perso.level=Niveau[0].salle;perso.levelinfo=Niveau[0];perso.x=perso.levelinfo.w-5;Actualiser_salle(perso);}
			//if ((perso.x==5) && (perso.y==6) && (perso.level==win)){ perso.x=6;perso.y=5;perso.level=niveau;Afficher_Perso(perso.x,perso.y,perso.level);Vie+=1;}
			//if (Vie == 0) {break;}
		}
	}

    	endwin();
	return 0;

}

