#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>
#include "structure.h"
#include "niveau.h"
#include "perso.h"


int kbhit(){
      struct termios oldt, newt;
      int ch;
      int oldf;
      tcgetattr(STDIN_FILENO, &oldt);
      newt = oldt;
      newt.c_lflag &= ~(ICANON | ECHO);
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
      oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
      fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
      ch = getchar();
      tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
      fcntl(STDIN_FILENO, F_SETFL, oldf);
      if(ch != EOF){
        ungetc(ch, stdin);
        return 1;
        }
      return 0;
}




WINDOW *Afficher_menu(){
	WINDOW *menu = newwin(LINES,COLS,0,0);
        refresh();

        box(menu,0,0);

	char menu_logo[7] = {" BBBBBB     AAAAAA   RRRRRRR   BBBBBB    IIIIIIII  EEEEEEEE           LL         AAAAAA   NN    NN  DDDDDD   ",
	                            " BB   BB   AA    AA  RR    RR  BB   BB      II     EE                 LL        AA    AA  NNN   NN  DD   DD  ",
				    " BB   BB   AA    AA  RR    RR  BB   BB      II     EE                 LL        AA    AA  NNNN  NN  DD    DD ",
         			    " BBBBBBB   AAAAAAAA  RRRRRRR   BBBBBBB      II     EEEEE     HHHHHH   LL        AAAAAAAA  NN NN NN  DD    DD ",
	         		    " BB    BB  AA    AA  RRRRR     BB    BB     II     EE                 LL        AA    AA  NN  NNNN  DD    DD ",
	         		    " BB    BB  AA    AA  RR  RRR   BB    BB     II     EE                 LL        AA    AA  NN   NNN  DD   DD  ",
		    		    " BBBBBBB   AA    AA  RR    RR  BBBBBBB   IIIIIIII  EEEEEEEE           LLLLLLLL  AA    AA  NN    NN  DDDDDD   ",
				    };

	for (int i = 0; i<7 ; i++){
		for (int j = 0; j<109 ; j++){
			if (*menu_logo[i][j] == " "){
				wattron(menu,COLOR_PAIR(3));
				mvwprintw(menu,i,j,"A");
				wattroff(menu,COLOR_PAIR(3));
			}
		}
	}

	mvwprintw(menu,LINES/2,(COLS/2)-23,"Appuyez sur une touche pour commencer à jouer");
        wrefresh(menu);

	return menu;
}

void Actualiser_menu(WINDOW *menu){
	werase(menu);
	wrefresh(menu);
	box(menu,0,0);

	char menu_logo[7] = {" BBBBBB     AAAAAA   RRRRRRR   BBBBBB    IIIIIIII  EEEEEEEE           LL         AAAAAA   NN    NN  DDDDDD   ",
                                    " BB   BB   AA    AA  RR    RR  BB   BB      II     EE                 LL        AA    AA  NNN   NN  DD   DD  ",
                                    " BB   BB   AA    AA  RR    RR  BB   BB      II     EE                 LL        AA    AA  NNNN  NN  DD    DD ",
                                    " BBBBBBB   AAAAAAAA  RRRRRRR   BBBBBBB      II     EEEEE     HHHHHH   LL        AAAAAAAA  NN NN NN  DD    DD ",
                                    " BB    BB  AA    AA  RRRRR     BB    BB     II     EE                 LL        AA    AA  NN  NNNN  DD    DD ",
                                    " BB    BB  AA    AA  RR  RRR   BB    BB     II     EE                 LL        AA    AA  NN   NNN  DD   DD  ",
                                    " BBBBBBB   AA    AA  RR    RR  BBBBBBB   IIIIIIII  EEEEEEEE           LLLLLLLL  AA    AA  NN    NN  DDDDDD   ",
                                    };

        for (int i = 0; i<7 ; i++){
                for (int j = 0; j<109 ; j++){
                        if (*menu_logo[i][j] == " "){
                                wattron(menu,COLOR_PAIR(3));
                                mvwprintw(menu,i,j,"A");
                                wattroff(menu,COLOR_PAIR(3));
                        }
                }
        }

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



void jeu()
{
		clear();
                refresh();

                WIN *Niveau = Creation_niveau();

		PERSO perso={10,10};
                MONSTRE monstre_salle1={20,10,Niveau[0]};

                perso.level = Niveau[1].salle;
                perso.levelinfo = Niveau[1];

                Afficher_Perso(perso.x,perso.y,perso.level);
                Afficher_Portail(5,5,Niveau[0].salle);
                Afficher_Portail(5,6,Niveau[1].salle);
                Afficher_Cailloux(10,10,Niveau[0].salle);
                Afficher_monstre(monstre_salle1.x,monstre_salle1.y,monstre_salle1.salle.salle);
                //Afficher_Vie(Vie);

                while(1)
                {
                        Afficher_Portail(5,5,Niveau[0].salle);
                        Afficher_Portail(5,6,Niveau[1].salle);
                        Afficher_Cailloux(10,10,Niveau[0].salle);
                        Afficher_monstre(monstre_salle1.x,monstre_salle1.y,monstre_salle1.salle.salle);
                        //Afficher_Vie(Vie);

                        Bouger_monstre(monstre_salle1);
                        if(kbhit()){
                        int ch=getch();
                        switch(ch)
                        {
                                case KEY_UP: if(perso.y>1) {--perso.y;Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
                                case KEY_DOWN: if(perso.y<perso.levelinfo.h-2) {++perso.y,Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
                                case KEY_RIGHT: if(perso.x<perso.levelinfo.w-3) {++perso.x;Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
                                case KEY_LEFT: if(perso.x>1) {--perso.x;Actualiser_salle(perso);}else{Actualiser_salle(perso);} break;
                        }

                        //if ((perso.x==2) && (perso.level==Niveau[1].salle)){werase(Niveau[1].salle);wrefresh(Niveau[1].salle);Niveau[1].salle=Creation_salle(Niveau[1].h,Niveau[1].w,Niveau>
                        //                                                      perso.level=Niveau[0].salle;perso.levelinfo=Niveau[0];perso.x=perso.levelinfo.w-5;Actualiser_salle(perso);}
                        //if ((perso.x==5) && (perso.y==6) && (perso.level==win)){ perso.x=6;perso.y=5;perso.level=niveau;Afficher_Perso(perso.x,perso.y,perso.level);Vie+=1;}
                        //iMONSTRE monstre_salle1={20,10,Niveau[0].salle};f (Vie == 0) {break;}
                        }
                        sleep(0.5);
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

	//int ch;
	//int Vie = 3;

	while(1)
	{
		Actualiser_menu(menu);
		if (kbhit()){

			int ch = getch();

			switch(ch){
				case KEY_BACKSPACE: endwin(); return 0; break;
				case KEY_ENTER: jeu();break;
			}
		}
		sleep(1);
	}

    	endwin();
	return 0;
}

