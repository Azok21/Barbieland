#include<stdlib.h>
#include<ncurses.h>
#include<time.h>
#include"structure.h"
#include"perso.h"

WINDOW *Creation_salle(int h,int w,int starty,int startx){
        WINDOW *salle = newwin(h,w,starty,startx);
        refresh();

        box(salle,0,0);
        wrefresh(salle);

        return salle;
}


WIN * Creation_niveau(){
        srand(time(NULL));

        static WIN Salles[4];

        Salles[0].startx=0;
        Salles[0].starty=0;
        Salles[0].h=LINES/2;
        Salles[0].w=COLS/2;
        Salles[0].salle = Creation_salle(Salles[0].h,Salles[0].w,Salles[0].starty,Salles[0].startx);

        for (int i = 2;i<5;i++){
                int h=0,w=0,startx=0,starty=0;
                switch(i){
                        case 2: Salles[1].startx=(COLS/2)+(rand()%(COLS/8));
				Salles[1].starty=rand()%(LINES/8);
				Salles[1].h=(rand()%((LINES/8)-Salles[1].starty))+(3*LINES/8);
				Salles[1].w=(rand()%((COLS/8)-(Salles[1].startx-(COLS/2))))+(3*COLS/8);
				Salles[1].salle = Creation_salle(Salles[1].h,Salles[1].w,Salles[1].starty,Salles[1].startx);
				break;
			case 3: Salles[2].startx=rand()%(COLS/8);
                                Salles[2].starty=(LINES/2)+(rand()%(LINES/8));
                                Salles[2].h=(rand()%((LINES/8)-(Salles[2].starty-(LINES/2))))+(3*LINES/8);
                                Salles[2].w=(rand()%((COLS/8)-Salles[2].startx))+(3*COLS/8);
                                Salles[2].salle = Creation_salle(Salles[2].h,Salles[2].w,Salles[2].starty,Salles[2].startx);
                                break;
			case 4: Salles[3].startx=(COLS/2)+(rand()%(COLS/8));
                                Salles[3].starty=(LINES/2)+(rand()%(LINES/8));
                                Salles[3].h=(rand()%((LINES/8)-(Salles[3].starty-(LINES/2))))+(3*LINES/8);
                                Salles[3].w=(rand()%((COLS/8)-(Salles[3].startx-(COLS/2))))+(3*COLS/8);
                                Salles[3].salle = Creation_salle(Salles[3].h,Salles[3].w,Salles[3].starty,Salles[3].startx);
                                break;
                }
        }
        return Salles;
}



void Afficher_Portail(int x,int y,WINDOW *win){
        wattron(win, COLOR_PAIR(3));
        mvwprintw(win,y,x,"p");
        wattroff(win, COLOR_PAIR(3));

        wrefresh(win);
}

void Afficher_monstre(int x,int y,WINDOW *win){
        wattron(win,COLOR_PAIR(4));
        mvwprintw(win,x,y,"M");
        wattroff(win,COLOR_PAIR(4));
        wrefresh(win);
}



void Actualiser_salle(PERSO perso){
        WINDOW *salle = perso.level;
        werase(salle);
        wrefresh(salle);
        box(salle,0,0);
        Afficher_Perso(perso.x,perso.y,salle);
	Afficher_Portail(5,6,salle);
}

void Actualiser_salle_monstre(MONSTRE monstre){
	WINDOW *salle = monstre.salle.salle;
	werase(salle);
	wrefresh(salle);
	box(salle,0,0);
	Afficher_monstre(monstre.x,monstre.y,salle);
	Afficher_Portail(5,6,salle);
}
