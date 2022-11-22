#include <ncurses.h>
#include <stdlib.h>


typedef struct param_win{ int h,w,startx,starty;}WIN;

typedef struct param_perso{ int x,y;WINDOW *level;WIN levelinfo;}PERSO;




void Afficher_menu(){
	WINDOW *menu = newwin(LINES,COLS,0,0);
        refresh();

        box(menu,0,0);
        mvwprintw(menu,LINES/2,(COLS/2)-23,"Appuyez sur une touche pour commencer à jouer");
        wrefresh(menu);
}


void Creation_niveau(){
}


void Creation_Salle(){
}



void Creation_liens(){
}



void Init_Couleur(){
	init_pair(1, COLOR_WHITE,COLOR_WHITE);
	init_pair(2, COLOR_GREEN,COLOR_GREEN);
	init_pair(3, COLOR_MAGENTA,COLOR_MAGENTA);
	init_pair(4, COLOR_RED,COLOR_RED);
}



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
	WIN Niveau={LINES/2,COLS/2,0,0};
	WIN Win={LINES/2,COLS/2,COLS/2,LINES/2};

	if (ch =getch())
	{
		clear();
		refresh();

		WINDOW *niveau = newwin(Niveau.h,Niveau.w,Niveau.starty,Niveau.startx);
		WINDOW *win = newwin(Win.h,Win.w,Win.starty,Win.startx);
		box(niveau,0,0);
		box(win,0,0);

		perso.level = niveau;
		perso.levelinfo = Niveau;

		Afficher_Perso(perso.x,perso.y,perso.level);
		Afficher_Portail(5,5,niveau);
                Afficher_Portail(5,6,win);
		Afficher_Vie(Vie);

		while((ch=getch()) != KEY_F(1))
		{
			werase(niveau);
			werase(win);

			box(niveau,0,0);
			box(win,0,0);

			Afficher_Portail(5,5,niveau);
                        Afficher_Portail(5,6,win);
			Afficher_Vie(Vie);

			switch(ch)
			{
				case KEY_UP: if(perso.y>perso.levelinfo.starty+1) {--perso.y;Afficher_Perso(perso.x,perso.y,perso.level);}else{Afficher_Perso(perso.x,perso.y,perso.level);} break;
				case KEY_DOWN: if(perso.y<(perso.levelinfo.h)-2) {++perso.y,Afficher_Perso(perso.x,perso.y,perso.level);}else{Afficher_Perso(perso.x,perso.y,perso.level);} break;
				case KEY_RIGHT: if(perso.x<(perso.levelinfo.w)-3) {++perso.x;Afficher_Perso(perso.x,perso.y,perso.level);}else{Afficher_Perso(perso.x,perso.y,perso.level);} break;
				case KEY_LEFT: if(perso.x>perso.levelinfo.startx+1) {--perso.x;Afficher_Perso(perso.x,perso.y,perso.level);}else{Afficher_Perso(perso.x,perso.y,perso.level);} break;
			}

			if ((perso.x==5) && (perso.y==5) && (perso.level==niveau)){ perso.x=6;perso.y=6;perso.level=win;Afficher_Perso(perso.x,perso.y,perso.level);}
			if ((perso.x==5) && (perso.y==6) && (perso.level==win)){ perso.x=6;perso.y=5;perso.level=niveau;Afficher_Perso(perso.x,perso.y,perso.level);Vie+=1;}
			if (Vie == 0) {break;}
		}
	}

    	endwin();
	return 0;

}
