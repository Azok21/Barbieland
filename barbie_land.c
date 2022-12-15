#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"
#include "niveau.h"
#include "perso.h"


void Init_Couleur(){
        init_pair(1, COLOR_WHITE,COLOR_WHITE);
        init_pair(2, COLOR_GREEN,COLOR_GREEN);
        init_pair(3, COLOR_MAGENTA,COLOR_MAGENTA);
        init_pair(4, COLOR_RED,COLOR_RED);
        init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
}

WINDOW *Afficher_menu(){
	WINDOW *menu = newwin(LINES,COLS,0,0);
        refresh();

        box(menu,0,0);

	mvwprintw(menu,LINES/2,(COLS/2)-11,"Appuyez sur une touche");
        wrefresh(menu);

	return menu;
}

void Actualiser_menu(WINDOW *menu){
	werase(menu);
	wrefresh(menu);
	box(menu,0,0);

	wattron(menu,COLOR_PAIR(6));
	mvwprintw(menu,5,COLS/2-54, " BBBBBB     AAAAAA   RRRRRRR   BBBBBB    IIIIIIII  EEEEEEEE           LL         AAAAAA   NN    NN  DDDDDD   ");
        mvwprintw(menu,6,COLS/2-54, " BB   BB   AA    AA  RR    RR  BB   BB      II     EE                 LL        AA    AA  NNN   NN  DD   DD  ");
        mvwprintw(menu,7,COLS/2-54, " BB   BB   AA    AA  RR    RR  BB   BB      II     EE                 LL        AA    AA  NNNN  NN  DD    DD ");
        mvwprintw(menu,8,COLS/2-54, " BBBBBBB   AAAAAAAA  RRRRRRR   BBBBBBB      II     EEEEE     HHHHHH   LL        AAAAAAAA  NN NN NN  DD    DD ");
        mvwprintw(menu,9,COLS/2-54, " BB    BB  AA    AA  RRRRR     BB    BB     II     EE                 LL        AA    AA  NN  NNNN  DD    DD ");
        mvwprintw(menu,10,COLS/2-54," BB    BB  AA    AA  RR  RRR   BB    BB     II     EE                 LL        AA    AA  NN   NNN  DD   DD  ");
        mvwprintw(menu,11,COLS/2-54," BBBBBBB   AA    AA  RR    RR  BBBBBBB   IIIIIIII  EEEEEEEE           LLLLLLLL  AA    AA  NN    NN  DDDDDD   ");
	wattroff(menu,COLOR_PAIR(6));

	mvwprintw(menu,LINES/2,(COLS/2)-18,    "Appuyez sur F2 pour commencer à jouer");
	mvwprintw(menu,LINES/2+2,(COLS/2)-20,"Appuyez sur F1 pour lire les instructions");
	mvwprintw(menu,LINES-2,1,"Appuyez sur BACKSPACE pour sortir");
	wrefresh(menu);
}

void Actualiser_info(WINDOW *menu,int ch){
	while(ch != KEY_BACKSPACE){
		werase(menu);
		wrefresh(menu);
		box(menu,0,0);

		wattron(menu, COLOR_PAIR(2));
		mvwprintw(menu,15,COLS/4,"P");
		wattroff(menu, COLOR_PAIR(2));
		mvwprintw(menu,15,COLS/4+2,"==> Votre Personnage");
		wrefresh(menu);
		ch = getch();
	}
}


void Afficher_Cailloux(int x,int y,WINDOW *win){
        wattron(win,COLOR_PAIR(5));
        mvwprintw(win,x,y,"°°");
        wattroff(win,COLOR_PAIR(5));
	wrefresh(win);
}

void Bouger_monstre(MONSTRE monstre){
	srand(time(NULL));
	int oldAction;
	int action = 1;
	switch(action){
		case 0: if(monstre.x>1 && oldAction!=2){--monstre.x;oldAction=0;Actualiser_salle_monstre(monstre);} break;
		case 1: if(monstre.y<monstre.salle.h-2 && oldAction!=3){++monstre.y;oldAction=1;Actualiser_salle_monstre(monstre);} break;
		case 2: if(monstre.x<monstre.salle.w-3 && oldAction!=1){++monstre.x;oldAction=2;Actualiser_salle_monstre(monstre);} break;
		case 3: if(monstre.y>1 && oldAction!=1){--monstre.y;oldAction=3;Actualiser_salle_monstre(monstre);} break;
		case 4: Actualiser_salle_monstre(monstre); break;
	}
}



void jeu(int ch)
{
	clear();
        refresh();

        WIN *Niveau = Creation_niveau();

	int Vie = 3;

	PERSO perso={10,10};
        MONSTRE monstre_salle1={20,10,Niveau[0]};

        perso.level = Niveau[1].salle;
        perso.levelinfo = Niveau[1];

        Afficher_Perso(perso.x,perso.y,perso.level);
	Afficher_Vie(Vie);

        Afficher_Portail(5,5,Niveau[0].salle);
        Afficher_Portail(5,6,Niveau[1].salle);

	Afficher_Cailloux(10,10,Niveau[0].salle);
        Afficher_monstre(monstre_salle1.x,monstre_salle1.y,monstre_salle1.salle.salle);

        while(ch != KEY_BACKSPACE)
        {
        	Afficher_Portail(5,5,Niveau[0].salle);
                Afficher_Portail(5,6,Niveau[1].salle);
                Afficher_Cailloux(10,10,Niveau[0].salle);
                Afficher_monstre(monstre_salle1.x,monstre_salle1.y,monstre_salle1.salle.salle);
                Afficher_Vie(Vie);

                Bouger_monstre(monstre_salle1);

		ch=getch();
                switch(ch)
                {
                	case KEY_UP: if(perso.y>1) {--perso.y;Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
                        case KEY_DOWN: if(perso.y<perso.levelinfo.h-2) {++perso.y,Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
                        case KEY_RIGHT: if(perso.x<perso.levelinfo.w-3) {++perso.x;Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
                        case KEY_LEFT: if(perso.x>1) {--perso.x;Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
                }

                //if ((perso.x==2) && (perso.level==Niveau[1].salle)){werase(Niveau[1].salle);wrefresh(Niveau[1].salle);Niveau[1].salle=Creation_salle(Niveau[1].h,Niveau[1].w,Niveau
                //                                                      perso.level=Niveau[0].salle;perso.levelinfo=Niveau[0];perso.x=perso.levelinfo.w-5;Actualiser_salle(perso);}
                //if ((perso.x==5) && (perso.y==6) && (perso.level==win)){ perso.x=6;perso.y=5;perso.level=niveau;Afficher_Perso(perso.x,perso.y,perso.level);Vie+=1;}
                //iMONSTRE monstre_salle1={20,10,Niveau[0].salle};f (Vie == 0) {break;}
	}
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

	WINDOW *menu = Afficher_menu();

	int ch=getch();
	//PlaySound("C:\Snakes and Ladders\snake.wav",NULL,SND_SYNC | SND_LOOP | SND_FILENAME);
	while(ch != KEY_BACKSPACE)
	{
		Actualiser_menu(menu);
		ch = getch();
		switch(ch){
			case KEY_F(1): Actualiser_info(menu,ch); break; 
			case KEY_F(2): jeu(ch);break;
		}
	}

    	endwin();
	return 0;
}

