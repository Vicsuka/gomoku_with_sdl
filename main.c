#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <time.h>
#include "fv.h"


int main(int argc, char *argv[]) {
///////////////////////////////////////////////////////////////////////////
//tárgyhonlapról sld inicializálása
    SDL_Surface *screen;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen=SDL_SetVideoMode(1280, 760, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    /**< SDL inicializalasa és ablak megnyitasa  */
////////////////////////////////////////////////////////////////////////////
    srand(time(NULL));
    SDL_TimerID id; //időzítő
    id = SDL_AddTimer(20, idozit, NULL);


    int select=0;
    while (1) {
    menu(screen);
    select= varakozas(screen);
    mod(screen ,select);
    SDL_FillRect(screen,NULL,0);
    }
    return 0;
}


