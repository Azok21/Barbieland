#ifndef HEADER_FILE_PERSO
#define HEADER_FILE_PERSO

typedef struct {
	int x,y;
	WINDOW *salle;
}PORTAIL;

typedef struct {
	int h,w,startx,starty;
	WINDOW *salle;
	PORTAIL portail1,portail2;
}WIN;

typedef struct {
	int x,y;
	WINDOW *level;
	WIN levelinfo;
}PERSO;

typedef struct {
	int x,y;
	WIN salle;
}MONSTRE;

#endif
