#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"
#include "niveau.h"
#include "perso.h"
#include "menu.h"


void Init_Couleur(){
        init_pair(1, COLOR_WHITE,COLOR_WHITE);
        init_pair(2, COLOR_GREEN,COLOR_GREEN);
        init_pair(3, COLOR_MAGENTA,COLOR_MAGENTA);
        init_pair(4, COLOR_RED,COLOR_RED);
        init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
}

void Bouger_monstre(MONSTRE monstre){
	srand(time(NULL));
	int oldAction;
	int action = 1;
	//if
}


void jeu(int ch)
{
	clear();
        refresh();

        WIN *Niveau = Creation_niveau();

	int Vie = 3;

	PERSO perso={10,10,Niveau[0].salle,Niveau[0]};
        MONSTRE monstre_salle1={20,10,Niveau[0]};

        Afficher_Perso(perso.x,perso.y,perso.level);
	Afficher_Vie(Vie);

	PORTAIL portail1_1 = {3*Niveau[0].w/4,Niveau[0].h-2,Niveau[0].salle};
	PORTAIL portail1_2 = {Niveau[0].w-2,Niveau[0].h/2,Niveau[0].salle};

	PORTAIL portail2_1 = {1,Niveau[1].h/2,Niveau[1].salle};
	PORTAIL portail2_2 = {Niveau[1].w/4,Niveau[1].h-2,Niveau[1].salle};

	PORTAIL portail3_1 = {3*Niveau[2].w/4,1,Niveau[2].salle};
        PORTAIL portail3_2 = {Niveau[2].w-2,Niveau[2].h/2,Niveau[2].salle};

	Niveau[0].portail1 = portail1_1;
	Niveau[0].portail2 = portail1_2;

	Niveau[1].portail1 = portail2_1;
        Niveau[1].portail2 = portail2_2;

	Niveau[2].portail1 = portail3_1;
	Niveau[2].portail2 = portail3_2;

	Afficher_Portail(portail1_1.x,portail1_1.y,portail1_1.salle);
        Afficher_Portail(portail1_2.x,portail1_2.y,portail1_2.salle);

	//Afficher_Cailloux(Niveau);
        //Afficher_monstre(monstre_salle1.x,monstre_salle1.y,monstre_salle1.salle.salle);

        while((ch != KEY_BACKSPACE) && (Vie != 0))
        {
        	Afficher_Portail(portail1_1.x,portail1_1.y,portail1_1.salle);
                Afficher_Portail(portail1_2.x,portail1_2.y,portail1_2.salle);
		//Afficher_Cailloux(Niveau);
                //Afficher_monstre(monstre_salle1.x,monstre_salle1.y,monstre_salle1.salle.salle);
                Afficher_Vie(Vie);

                //Bouger_monstre(monstre_salle1);

		ch=getch();
                switch(ch)
                {
                	case KEY_UP: if(perso.y>1) {--perso.y;Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
                        case KEY_DOWN: if(perso.y<perso.levelinfo.h-2) {++perso.y,Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
                        case KEY_RIGHT: if(perso.x<perso.levelinfo.w-2) {++perso.x;Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
                        case KEY_LEFT: if(perso.x>1) {--perso.x;Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
                }

                if ((perso.x==portail1_1.x) && (perso.y==portail1_1.y)){
			Vie-=1;
			perso.x = portail3_1.x;
			perso.y = portail3_1.y+1;
			perso.level = Niveau[2].salle;
			perso.levelinfo = Niveau[2];
			Actualiser_salle(perso);
		}
		if ((perso.x==portail1_2.x) && (perso.y==portail1_2.y)){
                        perso.x = portail2_1.x+1;
                        perso.y = portail2_1.y;
                        perso.level = Niveau[1].salle;
                        perso.levelinfo = Niveau[1];
                        Actualiser_salle(perso);
                }
		if ((perso.x==portail3_1.x) && (perso.y==portail3_1.y)){
                        perso.x = portail1_1.x;
                        perso.y = portail1_1.y-1;
                        perso.level = Niveau[0].salle;
                        perso.levelinfo = Niveau[0];
                        Actualiser_salle(perso);
                }
		if ((perso.x==portail2_1.x) && (perso.y==portail2_1.y)){
                        perso.x = portail1_2.x-1;
                        perso.y = portail1_2.y;
                        perso.level = Niveau[0].salle;
                        perso.levelinfo = Niveau[0];
                        Actualiser_salle(perso);
                }
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
			case KEY_F(1): Actualiser_menu_info(menu,ch); break;
			case KEY_F(2): jeu(ch);break;
		}
	}

    	endwin();
	return 0;
}

