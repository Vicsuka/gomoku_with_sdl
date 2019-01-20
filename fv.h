
void menu(SDL_Surface* screen);
/**< A menu kialakítása, alapveto utasitasokkal*/

int varakozas(SDL_Surface* screen);
/**< A menu resze, a kulonbozo elemek mozgatasaert felelos, visszateresi erteke, egy szam amivel tovabbmegy a program. */

int randomszam(int legkis, int legnagy);
/**< Egy random szamot general ket megadott szam kozott*/

void fel_le(SDL_Surface* screen,int hol);
/**< A sarga valasztodoboz mozgatasa fel- illetve lefele.*/

Uint32 idozit(Uint32 ms, void *param);
/**< SDL_usereventhez kellett, a targyhonlaprol masolva. */

void mod(SDL_Surface* screen, int select);
/**< Ez leptet tovabb a menubol attol fuggoen hogy mit valasztottunk */

void ujjatek(SDL_Surface* screen);
/**< uj jatek generalasa*/

void tolt_jatek(SDL_Surface* screen);
/**< Jatek vissza toltese*/

void toplista(SDL_Surface* screen);
/**< A toplista betoltese*/

void nev_be(SDL_Surface* screen,char* nev);
/**< Nev beolvasasa az uj jatek inditasa utan*/

void iksz(SDL_Surface* screen,int *forgas, int *forgas2);
/**< Az X nagyitasa,villogtatasa a fomenuben. */

void kor(SDL_Surface* screen,int *R,int *forditas);
/**< A kor nagyitasa,villogtatasa a fomenuben */

void pontadas(char*nev);
/**< Pont hozzaadasa txt-be */



