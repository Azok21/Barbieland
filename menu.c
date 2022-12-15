#include <ncurses.h>



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
        mvwprintw(menu,5,COLS/2-54, " BBBBBB     BBBBBB   BBBBBBB   BBBBBB    BBBBBBBB  BBBBBBBB           BB         BBBBBB   BB    BB  BBBBBB  ");
        mvwprintw(menu,6,COLS/2-54, " BB   BB   BB    BB  BB    BB  BB   BB      BB     BB                 BB        BB    BB  BBB   BB  BB   BB  ");
        mvwprintw(menu,7,COLS/2-54, " BB   BB   BB    BB  BB    BB  BB   BB      BB     BB                 BB        BB    BB  BBBB  BB  BB    BB ");
        mvwprintw(menu,8,COLS/2-54, " BBBBBBB   BBBBBBBB  BBBBBBB   BBBBBBB      BB     BBBBB     BBBBBB   BB        BBBBBBBB  BB BB BB  BB    BB ");
        mvwprintw(menu,9,COLS/2-54, " BB    BB  BB    BB  BBBBB     BB    BB     BB     BB                 BB        BB    BB  BB  BBBB  BB    BB ");
        mvwprintw(menu,10,COLS/2-54," BB    BB  BB    BB  BB  BBB   BB    BB     BB     BB                 BB        BB    BB  BB   BBB  BB   BB  ");
        mvwprintw(menu,11,COLS/2-54," BBBBBBB   BB    BB  BB    BB  BBBBBBB   BBBBBBBB  BBBBBBBB           BBBBBBBB  BB    BB  BB    BB  BBBBBB   ");
        wattroff(menu,COLOR_PAIR(6));

        mvwprintw(menu,LINES/2,(COLS/2)-18,    "Appuyez sur F2 pour commencer à jouer");
        mvwprintw(menu,LINES/2+2,(COLS/2)-20,"Appuyez sur F1 pour lire les instructions");
        mvwprintw(menu,LINES-2,1,"Appuyez sur BACKSPACE pour sortir");
        wrefresh(menu);
}


void Actualiser_menu_info(WINDOW *menu,int ch){
        while(ch != KEY_BACKSPACE){
                werase(menu);
                wrefresh(menu);
                box(menu,0,0);

                wattron(menu, COLOR_PAIR(2));
                mvwprintw(menu,15,COLS/4,"P");
                wattroff(menu, COLOR_PAIR(2));
                mvwprintw(menu,15,COLS/4+2,"==> Votre Personnage");

                wattron(menu, COLOR_PAIR(3));
                mvwprintw(menu,17,COLS/4,"O");
                wattroff(menu, COLOR_PAIR(3));
                mvwprintw(menu,17,COLS/4+2,"==> Les Portails ");

                wattron(menu, COLOR_PAIR(1));
                mvwprintw(menu,19,COLS/4,"R");
                wattroff(menu, COLOR_PAIR(1));
                mvwprintw(menu,19,COLS/4+2,"==> Les Roches INFRANCHISSABLES ");

                wattron(menu, COLOR_PAIR(4));
                mvwprintw(menu,21,COLS/4,"M");
                wattroff(menu, COLOR_PAIR(4));
                mvwprintw(menu,21,COLS/4+2,"==> Les Monstres ");

                wattron(menu, COLOR_PAIR(5));
		mvwprintw(menu,23,COLS/4,"C");
		wattroff(menu, COLOR_PAIR(5));
		mvwprintw(menu,23,COLS/4+2,"==> Les Coffres magiques ");
		mvwprintw(menu,24,COLS/4+5,"(en cours de construction)");

		mvwprintw(menu,17,COLS/2+15,"Vous venez d'entrer dans l'univers du jeu");
		mvwprintw(menu,19,COLS/2+30,"BARBIE-LAND");
		mvwprintw(menu,21,COLS/2+13,"Votre niveau de vie s'affiche en bas a gauche");

		mvwprintw(menu,30,COLS/4+28,"^");
		mvwprintw(menu,31,COLS/4+25,"<- | ->  ==> Commandes pour gerer les déplacements");
		mvwprintw(menu,32,COLS/4+28,"v");

		wrefresh(menu);
                ch = getch();
        }
}
