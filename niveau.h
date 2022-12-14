#ifndef HEADER_FILE_NIVEAU
#define HEADER_FILE_NIVEAU
WINDOW *Creation_salle(int h, int w, int starty, int startx);

WIN * Creation_niveau();

void Afficher_Portail(int x,int y,WINDOW *win);
void Afficher_monstre(int x,int y,WINDOW *win);

void Actualiser_salle(PERSO perso);
void Actualiser_salle_monstre(MONSTRE monstre);

#endif
