#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "fv.h"

const int szelesseg = 1280;
/**< A kepernyo szelessege*/

const int magassag = 760;
/**< A kepernyo magassaga*/


Uint32 idozit(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}

void menu(SDL_Surface* screen) {
    SDL_WM_SetCaption("Amoba", "Jatekra fel!");
    stringRGBA(screen, 200, 740, "Amoba", 255, 255, 255, 255);
    SDL_Flip(screen); /** \return Legalapvetobb menu letrehozasa */
}

/** \brief Randomszám letrehozasa
 *
 * \param legkis :legkisebb lehetseges ertek.
 * \param legnagy :legnagyobb lehetseges ertek.
 * \return A random szamot adja vissza.
 *
 */
int randomszam(int legkis, int legnagy) {
    int r = legkis;
    int kul = legnagy-legkis;
    r = legkis + rand() % kul + 1;
    return r;
}

/** \brief Varakozas
 *
 * \param valaszas A legfontosabb valtozo, ezzel fog tovabbmenni a program
 * \param novekvo A csik vizszintes csusztatasa
 * \param box_en Engedelyezi majd a doboz rajzolasat
 * \param forgas Az x novekedese/csokkentese
 * \param forgas2 Az x novekedese/csokkentese ellentetes iranyban
 * \param R A kor sugara
 * \param forditas Az erteke 1/0 ettol fordul meg a kor sugaranak novekedese/csokkenese
 * \return Visszaadja annak a menopontnak az erteket amit a felhasznalo valasztott
 *
 */
int varakozas(SDL_Surface* screen) {
    int valasztas = 0;
    int novekvo = 0;
    int box_en = 0;
    int forgas = -40;
    int forgas2 = 40;
    int R = 1;
    int forditas = 0;
    SDL_Event ev;
    while (1) {
        SDL_WaitEvent(&ev);
            switch (ev.type) {
            case SDL_USEREVENT:

                //Alul a felirat mozgatása egy csíkban
                if (novekvo>800) novekvo= -200;
                stringRGBA(screen, novekvo, 740, "Amoba         2015. 11. 14.       Horvath Mark", 0, 255, 255, 255);
                novekvo += 1;
                iksz(screen,&forgas,&forgas2);
                kor(screen,&R,&forditas);
                break;
                // Ha a felhasználó megnyom egy gombot mi történjen.
            case SDL_KEYDOWN:
                switch (ev.key.keysym.sym) {
                        case SDLK_UP:
                            //Felfele nyíl megnyomásakor
                        if (valasztas>0){
                        fel_le(screen,valasztas);
                        valasztas = valasztas - 1;
                        }
                        else valasztas = 3;
                        box_en = 1;
                        break;

                        case SDLK_DOWN:
                            //Lefele nyíl megnyomásakor
                        if (valasztas<3){
                        fel_le(screen,valasztas);
                        valasztas = valasztas +1;
                        }
                        else valasztas = 0;
                        box_en = 1;
                        break;
                        case SDLK_RETURN:
                            //Enter megnyomásakor mindenképpen el kell mennünk valahová
                            switch (valasztas) {
                                case 0:
                                    return 0;
                                break;

                                case 1:
                                    return 1;
                                break;

                                case 2:
                                    return 2;
                                break;

                                case 3:
                                    SDL_Quit();
                                    exit("Program kilepes\n");
                                break;
                            }
                }

                break;
            }

            //Formalitás megtartása
            if (box_en) fel_le(screen,valasztas);
            stringRGBA(screen, (szelesseg/3), (magassag/5), "Uj Jatek", 255,0,0, 255);
            stringRGBA(screen, (szelesseg/3), (magassag/5*2), "Jatek Betoltese",  255,0,0, 255);
            stringRGBA(screen, (szelesseg/3), (magassag/5*3), "Toplista",  255,0,0, 255);
            stringRGBA(screen, (szelesseg/3), (magassag/5*4), "Kilepes",  255,0,0, 255);
            //Képernyõ kitisztítása
            SDL_Flip(screen);
            SDL_FillRect(screen,NULL,0);
            }

}

void fel_le(SDL_Surface* screen,int hol){
    //255 255 0 sárga
    //függõleges vonalak
    lineRGBA(screen, szelesseg/3 - 10 , magassag/5 + hol*magassag/5 + 20,szelesseg/3 - 10 , magassag/5 + hol*magassag/5 - 20, 255,255,0, 255);
    lineRGBA(screen, szelesseg/3 + 120, magassag/5 + hol*magassag/5 + 20,szelesseg/3 + 120, magassag/5 + hol*magassag/5 - 20, 255,255,0, 255);
    //vízszintes vonalak
    lineRGBA(screen, szelesseg/3 - 10, magassag/5 + hol*magassag/5 + 20,szelesseg/3 + 120, magassag/5 + hol*magassag/5 + 20, 255,255,0, 255);
    lineRGBA(screen, szelesseg/3 - 10, magassag/5 + hol*magassag/5 - 20,szelesseg/3 + 120, magassag/5 + hol*magassag/5 - 20, 255,255,0, 255);
    SDL_Flip(screen);
}

void mod(SDL_Surface* screen,int select) {
    switch (select) {
    case 0:ujjatek(screen); break;
    case 1:tolt_jatek(screen); break;
    case 2:toplista(screen); break;
    }
}

void ujjatek (SDL_Surface* screen) {
    SDL_FillRect(screen,NULL,0);
    unsigned *tabla;
    int meret; int eredmeny;
    char nev[40]="";
    nev_be(screen,&nev);
    meret = jatek_meret(screen);
    tabla = jatek_init(meret);
    eredmeny = jatek_start(screen,meret,tabla,0,0);
    if (eredmeny == 1) pontadas(&nev);
    free(tabla);
}

/** \brief Az elmentett jatek betoltese
 *
 * \param nevbe : A beolvasott nev atmeneti tarolasa
 * \param szamlalo : Szamolja az eddig csak egyszer talalt nevek szamat
 *
 */

void tolt_jatek(SDL_Surface* screen) {
    unsigned *tabla;
    int meret;
    int lepes;
    int eredmeny;
    int i=0;
    char nev[40]="";
    nev_be(screen,&nev);
    FILE *f = fopen("load.txt","r");
    fscanf(f, "%d", &meret);
    tabla = malloc (meret*meret*sizeof(unsigned));
    fscanf(f, "%d", &lepes);
    while(!feof(f)) {
        fscanf(f,"%u",&tabla[i]);
        i += 1;
    }
    fclose(f);
    eredmeny = jatek_start(screen,meret,tabla,1,lepes);
    if (eredmeny == 1) pontadas(&nev);
    free(tabla);
}

/** \brief Azoknak a jatekosoknak a kiirasa akiknak sikerult megverni a gepet
 *
 * \param nevbe : A beolvasott nev atmeneti tarolasa
 * \param szamlalo : Szamolja az eddig csak egyszer talalt nevek szamat
 *
 */
void toplista(SDL_Surface* screen) {
    FILE *f = fopen("top.txt","r");
    SDL_Event ev;
    char nevbe[40];
    int pont=0;
    int ki=1;
    int i=0;
    int j;
    int szamlalo = 0;
    char jatekosok[20][40];
    for(j=0;j<20;j++)
        strcpy(jatekosok[j],"");
    while(!feof(f)) {
            fscanf(f, "%s", nevbe);
            strcpy(jatekosok[i],nevbe);
            i +=1;
        }
    for(j=0;j<20;j++) {
        for(i=j+1;i<20;i++) {
                if ((strcmp(jatekosok[j],jatekosok[i]))==0) pont = 1;
        }
        if (!pont) {
            stringRGBA(screen,200,50 + szamlalo*50, jatekosok[j],150,210,100,255);
            szamlalo += 1;
        }
        pont = 0;
    }
    SDL_Flip(screen);
    while (ki) {
        SDL_WaitEvent(&ev);
            switch (ev.type) {
                case SDL_USEREVENT:
                    break;
                case SDL_KEYDOWN:
                    switch (ev.key.keysym.sym) {
                        case SDLK_ESCAPE:ki=0; break;
                    }
            }
    }
    fclose(f);

}

/** \brief A nev beolvasasa
 *
 * \param nev : Ebben tarolodik el a nev
 */
void nev_be(SDL_Surface* screen, char* nev) {
    SDL_EnableUNICODE(SDL_ENABLE);
    int i=0;
    int ki=1;
    SDL_Event ev;
    while (ki) {
        SDL_WaitEvent(&ev);
        switch (ev.type) {
            case SDL_USEREVENT:
                break;
            case SDL_KEYDOWN:
                nev[i] = ev.key.keysym.unicode;
                i +=1 ;
                switch (ev.key.keysym.sym) {
                    case SDLK_RETURN : ki = 0; break;
                    case SDLK_BACKSPACE: i -= 2; break;
                }
                break;
        }
        stringRGBA(screen, szelesseg/4, magassag/3 + 20, nev, 255, 255, 255, 255);
        stringRGBA(screen,szelesseg/4,magassag/3,"Kerem adjon meg egy nevet!",255,255,0,255);
        SDL_Flip(screen);
        SDL_FillRect(screen,NULL,0);
    }
}

/** \brief Az iksz kirajzolasa
 *
 * \param forgas Az ellentetes novekedeshez kell.
 * \param forgas2 Az ellentetes novekedeshez kell.
 *
 *
 */

void iksz(SDL_Surface* screen,int *forgas, int *forgas2) {
    if (*forgas < 60) {
                    lineRGBA(screen, szelesseg-200, magassag/2,szelesseg-200 + *forgas, magassag/2 + *forgas2, randomszam(0,255),randomszam(0,255),randomszam(0,255), 255);
                    lineRGBA(screen, szelesseg-200, magassag/2,szelesseg-200 + *forgas2, magassag/2 - *forgas, randomszam(0,255),randomszam(0,255),randomszam(0,255), 255);
                } else *forgas = -60;
    if (*forgas2 > -60){
                    lineRGBA(screen, szelesseg-200, magassag/2,szelesseg-200 + *forgas2, magassag/2 + *forgas, randomszam(0,255),randomszam(0,255),randomszam(0,255), 255);
                    lineRGBA(screen, szelesseg-200, magassag/2,szelesseg-200 + *forgas, magassag/2 - *forgas2, randomszam(0,255),randomszam(0,255),randomszam(0,255), 255);
                } else *forgas2 = 60;
    *forgas +=1;
    *forgas2 -=1;
};

/** \brief A kor rajzolasa. Kicsit hasonlit az iksz-hez, bar logikailag ellentetes.
 *
 * \param R A rajzolando kor sugara
 * \param forditas Ha aktivalodik akkor csokken a kor sugara, ha passziv akkor pedig no.
 *
 *
 */

void kor(SDL_Surface* screen,int *R, int *forditas) {
    if (*forditas == 0) {
        circleRGBA(screen, szelesseg-400, magassag/2,*R,randomszam(0,255),randomszam(0,255),randomszam(0,255),255);
        *R += 1;
        if (*R > 60) *forditas = 1;
    }
    else {
        circleRGBA(screen, szelesseg-400, magassag/2,*R,randomszam(0,255),randomszam(0,255),randomszam(0,255),255);
        *R -= 1;
        if (*R < 2) *forditas = 0;
        }
}

void pontadas(char*nev) {
    FILE *f = fopen("top.txt","a");
    fprintf(f,"%s\n",nev);
    fclose(f);
}
