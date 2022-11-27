#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct param_win{int h,w,startx,starty;}WIN;

typedef struct param_perso{ int x,y;WINDOW *level;WIN levelinfo;}PERSO;




void Afficher_menu(){
	WINDOW *menu = newwin(LINES,COLS,0,0);
        refresh();

        box(menu,0,0);
        mvwprintw(menu,LINES/2,(COLS/2)-23,"Appuyez sur une touche pour commencer à jouer");
        wrefresh(menu);
}



WINDOW *Creation_salle(int h,int w,int starty,int startx){
        WINDOW *salle = newwin(h,w,starty,startx);
        refresh();

        box(salle,0,0);
        wrefresh(salle);

        return salle;
}



void Creation_niveau(){
	srand(time(NULL));

	WINDOW *salle_trone = Creation_salle(LINES/2,COLS/2,0,0);

	for (int i = 2;i<5;i++){
		int h=0,w=0,startx=0,starty=0;
		switch(i){
			case 2: startx=(COLS/2)+(rand()%(COLS/8));
				starty=rand()%(LINES/8);
				h=(rand()%((LINES/8)-starty))+(3*LINES/8);
				w=(rand()%((COLS/8)-(startx-(COLS/2))))+(3*COLS/8);
				WINDOW *salle2 = Creation_salle(h,w,starty,startx);
				break;
			case 3: startx=rand()%(COLS/8);
                                starty=(LINES/2)+(rand()%(LINES/8));
                                h=(rand()%((LINES/8)-(starty-(LINES/2))))+(3*LINES/8);
                                w=(rand()%((COLS/8)-startx))+(3*COLS/8);
                                WINDOW *salle3 = Creation_salle(h,w,starty,startx);
                                break;
			case 4: startx=(COLS/2)+(rand()%(COLS/8));
                                starty=(LINES/2)+(rand()%(LINES/8));
                                h=(rand()%((LINES/8)-(starty-(LINES/2))))+(3*LINES/8);
                                w=(rand()%((COLS/8)-(startx-(COLS/2))))+(3*COLS/8);
                                WINDOW *salle4 = Creation_salle(h,w,starty,startx);
                                break;
		}
	}
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

		Creation_niveau();

		//WINDOW *niveau = Creation_salle(Niveau.h,Niveau.w,Niveau.starty,Niveau.startx);
		//WINDOW *win = Creation_salle(Win.h,Win.w,Win.starty,Win.startx);

		//perso.level = niveau;
		//perso.levelinfo = Niveau;

		//Afficher_Perso(perso.x,perso.y,perso.level);
		//Afficher_Portail(5,5,niveau);
                //Afficher_Portail(5,6,win);
		//Afficher_Vie(Vie);

		while((ch=getch()) != KEY_F(1))
		{
			//werase(niveau);
			//werase(win);

			//box(niveau,0,0);
			//box(win,0,0);

			//Afficher_Portail(5,5,niveau);
                        //Afficher_Portail(5,6,win);
			//Afficher_Vie(Vie);

			//switch(ch)
			//{
			//	case KEY_UP: if(perso.y>perso.levelinfo.starty+1) {--perso.y;Afficher_Perso(perso.x,perso.y,perso.level);}else{Afficher_Perso(perso.x,perso.y,perso.level);} break;
			//	case KEY_DOWN: if(perso.y<(perso.levelinfo.h)-2) {++perso.y,Afficher_Perso(perso.x,perso.y,perso.level);}else{Afficher_Perso(perso.x,perso.y,perso.level);} break;
			//	case KEY_RIGHT: if(perso.x<(perso.levelinfo.w)-3) {++perso.x;Afficher_Perso(perso.x,perso.y,perso.level);}else{Afficher_Perso(perso.x,perso.y,perso.level);} break;
			//	case KEY_LEFT: if(perso.x>perso.levelinfo.startx+1) {--perso.x;Afficher_Perso(perso.x,perso.y,perso.level);}else{Afficher_Perso(perso.x,perso.y,perso.level);} break;
			//}

			//if ((perso.x==5) && (perso.y==5) && (perso.level==niveau)){ perso.x=6;perso.y=6;perso.level=win;Afficher_Perso(perso.x,perso.y,perso.level);}
			//if ((perso.x==5) && (perso.y==6) && (perso.level==win)){ perso.x=6;perso.y=5;perso.level=niveau;Afficher_Perso(perso.x,perso.y,perso.level);Vie+=1;}
			//if (Vie == 0) {break;}
		}
	}

    	endwin();
	return 0;

}
