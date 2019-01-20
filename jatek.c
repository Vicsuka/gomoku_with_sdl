#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <time.h>
#include "fv.h"
#include "jatek.h"

/** \brief Randomszam letrehozasa
 *
 * \param meret : meret kivalasztasa
 * \param ki :kiugras engedelyezese
 * \return A jatek meretet adja vissza
 *
 */

int jatek_meret(SDL_Surface* screen) {
    int meret=6,ki=1;
    SDL_FillRect(screen,NULL,0);
    boxRGBA(screen, 375, 150, 390, 155, 100, 200, 100, 255);
    SDL_Event ev;
    while (ki) {
    SDL_WaitEvent(&ev);
    switch (ev.type) {
            case SDL_USEREVENT:
                SDL_Flip(screen);
                break;
            case SDL_KEYDOWN:
                    switch (ev.key.keysym.sym) {
                    case SDLK_UP:
                        if (meret==6) meret=14;
                         else
                        meret -= 1;
                        break;
                    case SDLK_DOWN:
                        if (meret==14) meret =6;
                        else meret +=1 ;
                        break;
                    case SDLK_RETURN : return meret; break;
                    }
                    break;
                }
    boxrajz(screen,meret);
    stringRGBA(screen, 400, 150, "6 x 6", 255, 255, 255, 255);
    stringRGBA(screen, 400, 200, "7 x 7", 255, 255, 255, 255);
    stringRGBA(screen, 400, 250, "8 x 8", 255, 255, 255, 255);
    stringRGBA(screen, 400, 300, "9 x 9", 255, 255, 255, 255);
    stringRGBA(screen, 400, 350, "10 x 10", 255, 255, 255, 255);
    stringRGBA(screen, 400, 400, "11 x 11", 255, 255, 255, 255);
    stringRGBA(screen, 400, 450, "12 x 12", 255, 255, 255, 255);
    stringRGBA(screen, 400, 500, "13 x 13", 255, 255, 255, 255);
    stringRGBA(screen, 400, 550, "14 x 14", 255, 255, 255, 255);
    SDL_Flip(screen);
    SDL_FillRect(screen,NULL,0);
    }
}

void boxrajz(SDL_Surface* screen,int meret) {
    boxRGBA(screen, 375, 150 + (meret-6)*50, 390, 155 + (meret-6)*50, 100, 200, 100, 255);
}

unsigned* jatek_init(int meret) {
    return malloc (meret*meret*sizeof(unsigned));
}

/** \brief Jatek inditasa
 *
 * \param lepes : lepes szamlalasa
 * \param t_lepes : lepesszam amikor toltes van
 * \param jatek :kiugras engedelyezese, erteke 1-2-3: 1 a jatekos nyer, 2 a gep nyer, 3 ESC-el kileptek
 * \return A kilepest kodjat adja vissza
 *
 */
int jatek_start(SDL_Surface* screen,int meret,unsigned* tabla,int toltes,int t_lepes){
    int kezdes;
    int lepes;
    if (!toltes) {
            int kezdes = (randomszam(1,4)%2);
            int lepes = kezdes;}
    else lepes = t_lepes;
    int jatek = 0;
    int x=0,y=0;
    int rakott=0;
    if (!toltes) nullaz(tabla,meret);
    SDL_Event ev;
    while (jatek==0) {
            SDL_WaitEvent(&ev);
            switch (ev.type) {
            case SDL_USEREVENT:
                break;
            case SDL_KEYDOWN:
                    switch (ev.key.keysym.sym) {
                    case SDLK_UP:
                        if (y == 0) y=meret-1;
                        else y -=1;
                        break;
                    case SDLK_DOWN:
                        if (y == meret-1) y=0;
                        else y +=1;
                        break;
                    case SDLK_RIGHT:
                        if (x == meret-1) x=0;
                        else x +=1;
                        break;
                    case SDLK_LEFT:
                        if (x == 0) x=meret-1;
                        else x -=1;
                        break;
                    case SDLK_RETURN:
                        if ((lepes%2) == 0) {
                        if (tabla[y*meret+x]==0){
                        tabla[y*meret+x]= 1;
                        if (!toltes) kezdes = 1;
                        lepes += 1;}
                        }
                        break;
                    case SDLK_ESCAPE:
                        jatek = 3;
                        break;
                    case SDLK_s:
                        mentes(tabla,meret,lepes);
                        break;
                    }
                    break;
                }
    if(!toltes) {
        if (!kezdes) {
            stringRGBA(screen, 800, 20, "Te kezdesz!", 255, 255, 255, 255);
        }
    }
    if (lepes == 1)
            if(tabla[(meret*meret)/2+meret/2]==0) {
            tabla[(meret*meret)/2+meret/2]=2;
            lepes+=1;
            }
    if ((lepes%2) == 1){
        rakott = geprak(screen,tabla,meret);
        if (rakott) lepes +=1;
        rakott=0;
    }
    mozgas(screen,x,y);
    nyert(screen,tabla,meret,&jatek);
    tablarajz(screen,meret,tabla);
    SDL_Flip(screen);
    SDL_FillRect(screen,NULL,0);
    }
}


void tablarajz(SDL_Surface* screen,int meret,unsigned* tabla) {
    int i,j;
    for (i = 1;i <= meret;i++)
        for (j = 1;j <= meret;j++) {
            rectangleRGBA(screen, 200 + j*50, 0 + i*50, 250 + j*50, 50 + i*50,255, 100, 255, 255);
            if (tabla[(i-1)*meret+(j-1)]==1) circleRGBA(screen, 225 + j*50, 25 + i*50, 10, 255, 255, 0, 255);
            if (tabla[(i-1)*meret+(j-1)]==2) circleRGBA(screen, 225 + j*50, 25 + i*50, 10, 0, 255, 255, 255);
        }
}

void nullaz(unsigned* tabla,int meret) {
    int i;
    for (i=0; i<(meret*meret);i++)
        tabla[i]=0;
}

void mozgas(SDL_Surface* screen,int x,int y){
    circleRGBA(screen, 275 + x*50, 75 + y*50, 5, 255, 0, 0, 200);
}

/** \brief Gep rakasanak helye
 *
 * \param dontes : A sulyzott tablabol a legnagyobb ertek
 * \param index : Az a mezo ahova legvegul rak a gep
 * \param jatek :kiugras engedelyezese, erteke 1-2-3: 1 a jatekos nyer, 2 a gep nyer, 3 ESC-el kileptek
 * \return Ha lett dontes akkor 1,egyebkent 0 a visszateresi ertek
 *
 */

int geprak(SDL_Surface* screen,unsigned* tabla,int meret){
    int dontes,index=0;
    int i;
    unsigned* tablasuly=tablascan(tabla,meret);
    save(tabla,tablasuly,meret);
    dontes = 0;
    for(i=1;i<meret*meret;i++)
      if (dontes<=tablasuly[i]){
            if (tabla[i]==0) {
            dontes = tablasuly[i];
            index = i;}
        }
    if (tabla[index]==0){
        tabla[index] = 2;
        return 1;
    }
    free (tablasuly);
    return 0;
}

/** \brief A tabla sulyozasa
 *
 * \param ellenseges : Az eppen vizsgalando mezo, ennek kornyezetet vizsgaljuk veszelyekert
 * \param szint : A veszely szintje, minden mezonek van ilyen erteke
 * \param jatek :kiugras engedelyezese, erteke 1-2-3: 1 a jatekos nyer, 2 a gep nyer, 3 ESC-el kileptek
 * \return Visszaadja a megcsinalt sulyozott tablanak memoriacimet
 *
 */
unsigned* tablascan(unsigned* tabla,int meret){
    int i,j;
    int ellenseges;
    int szint;
    unsigned* tablasuly = malloc (meret*meret*sizeof(unsigned));
     for (i = 0;i < meret;i++)
        for (j = 0;j < meret;j++) {
            ellenseges = i*meret+j;
            szint = 0;
            //sajat
                if (tabla[ellenseges+1]==2) szint+=2;
                if (tabla[ellenseges-1]==2) szint+=2;
                if (tabla[ellenseges+2]==2) szint+=1;
                if (tabla[ellenseges-2]==2) szint+=1;

                if ((tabla[ellenseges+1]==2) &&  (tabla[ellenseges+2]==2)) szint+=14;
                if ((tabla[ellenseges-1]==2) &&  (tabla[ellenseges-2]==2)) szint+=14;

                if ((tabla[ellenseges+1]==2) &&  (tabla[ellenseges+2]==2) && (tabla[ellenseges+3]==2)) szint+=290;
                if ((tabla[ellenseges-1]==2) &&  (tabla[ellenseges-2]==2) && (tabla[ellenseges-3]==2)) szint+=290;

                if ((tabla[ellenseges+1]==2) &&  (tabla[ellenseges+2]==2) && (tabla[ellenseges+3]==2) && (tabla[ellenseges+4]==2)) szint+=2900;
                if ((tabla[ellenseges-1]==2) &&  (tabla[ellenseges-2]==2) && (tabla[ellenseges-3]==2) && (tabla[ellenseges-4]==2)) szint+=2900;
                    //oszlop
                if (tabla[ellenseges-meret]==2) szint+=2;
                if (tabla[ellenseges+meret]==2) szint+=2;
                if (tabla[ellenseges-meret*2]==2)szint+=1;
                if (tabla[ellenseges+meret*2]==2)szint+=1;

                if ((tabla[ellenseges-meret]==2) && (tabla[ellenseges-meret*2]==2)) szint+=14;
                if ((tabla[ellenseges+meret]==2) && (tabla[ellenseges+meret*2]==2)) szint+=14;

                if ((tabla[ellenseges-meret]==2) &&  (tabla[ellenseges-meret*2]==2) && (tabla[ellenseges-meret*3]==2)) szint+=290;
                if ((tabla[ellenseges+meret]==2) &&  (tabla[ellenseges+meret*2]==2) && (tabla[ellenseges+meret*3]==2)) szint+=290;

                if ((tabla[ellenseges-meret]==2) &&  (tabla[ellenseges-meret*2]==2) && (tabla[ellenseges-meret*3]==2) && (tabla[ellenseges-meret*4]==2)) szint+=2900;
                if ((tabla[ellenseges+meret]==2) &&  (tabla[ellenseges+meret*2]==2) && (tabla[ellenseges+meret*3]==2) && (tabla[ellenseges+meret*4]==2)) szint+=2900;
                    //atlo
                if (tabla[ellenseges+meret+1]==2) szint+=2;
                if (tabla[ellenseges+meret-1]==2) szint+=2;
                if (tabla[ellenseges-meret+1]==2) szint+=2;
                if (tabla[ellenseges-meret-1]==2) szint+=2;

                if ((tabla[ellenseges+meret+1]==2) && (tabla[ellenseges+2*meret+2]==2)) szint+=14;
                if ((tabla[ellenseges-meret-1]==2) && (tabla[ellenseges-2*meret-2]==2)) szint+=14;
                if ((tabla[ellenseges+meret-1]==2) && (tabla[ellenseges+2*meret-2]==2)) szint+=14;
                if ((tabla[ellenseges-meret+1]==2) && (tabla[ellenseges-2*meret+2]==2)) szint+=14;

                if ((tabla[ellenseges+meret+1]==2) &&  (tabla[ellenseges+meret*2+2]==2) && (tabla[ellenseges+meret*3+3]==2)) szint+=290;
                if ((tabla[ellenseges-meret-1]==2) &&  (tabla[ellenseges-meret*2-2]==2) && (tabla[ellenseges-meret*3-3]==2)) szint+=290;
                if ((tabla[ellenseges+meret-1]==2) &&  (tabla[ellenseges+meret*2-2]==2) && (tabla[ellenseges+meret*3-3]==2)) szint+=290;
                if ((tabla[ellenseges-meret+1]==2) &&  (tabla[ellenseges-meret*2+2]==2) && (tabla[ellenseges-meret*3+3]==2)) szint+=290;

                if ((tabla[ellenseges+meret+1]==2) &&  (tabla[ellenseges+meret*2+2]==2) && (tabla[ellenseges+meret*3+3]==2) && (tabla[ellenseges+meret*4+4]==2)) szint+=2900;
                if ((tabla[ellenseges-meret-1]==2) &&  (tabla[ellenseges-meret*2-2]==2) && (tabla[ellenseges-meret*3-3]==2) && (tabla[ellenseges-meret*4-4]==2)) szint+=2900;
                if ((tabla[ellenseges+meret-1]==2) &&  (tabla[ellenseges+meret*2-2]==2) && (tabla[ellenseges+meret*3-3]==2) && (tabla[ellenseges+meret*4-4]==2)) szint+=2900;
                if ((tabla[ellenseges-meret+1]==2) &&  (tabla[ellenseges-meret*2+2]==2) && (tabla[ellenseges-meret*3+3]==2) && (tabla[ellenseges-meret*4+4]==2)) szint+=2900;
            //ellenseg
                    //sor
                if (tabla[ellenseges+1]==1) szint+=3;
                if (tabla[ellenseges-1]==1) szint+=3;
                if (tabla[ellenseges+2]==1) szint+=2;
                if (tabla[ellenseges-2]==1) szint+=2;

                if ((tabla[ellenseges+1]==1) &&  (tabla[ellenseges+2]==1)) szint+=15;
                if ((tabla[ellenseges-1]==1) &&  (tabla[ellenseges-2]==1)) szint+=15;

                if ((tabla[ellenseges+1]==1) &&  (tabla[ellenseges+2]==1) && (tabla[ellenseges+3]==1)) szint+=300;
                if ((tabla[ellenseges-1]==1) &&  (tabla[ellenseges-2]==1) && (tabla[ellenseges-3]==1)) szint+=300;
                    //oszlop
                if (tabla[ellenseges-meret]==1) szint+=3;
                if (tabla[ellenseges+meret]==1) szint+=3;
                if (tabla[ellenseges-meret*2]==1)szint+=2;
                if (tabla[ellenseges+meret*2]==1)szint+=2;

                if ((tabla[ellenseges-meret]==1) && (tabla[ellenseges-meret*2]==1)) szint+=15;
                if ((tabla[ellenseges+meret]==1) && (tabla[ellenseges+meret*2]==1)) szint+=15;

                if ((tabla[ellenseges-meret]==1) &&  (tabla[ellenseges-meret*2]==1) && (tabla[ellenseges-meret*3]==1)) szint+=300;
                if ((tabla[ellenseges+meret]==1) &&  (tabla[ellenseges+meret*2]==1) && (tabla[ellenseges+meret*3]==1)) szint+=300;
                    //atlo
                if (tabla[ellenseges+meret+1]==1) szint+=3;
                if (tabla[ellenseges+meret-1]==1) szint+=3;
                if (tabla[ellenseges-meret+1]==1) szint+=3;
                if (tabla[ellenseges-meret-1]==1) szint+=3;

                if ((tabla[ellenseges+meret+1]==1) && (tabla[ellenseges+2*meret+2]==1)) szint+=15;
                if ((tabla[ellenseges-meret-1]==1) && (tabla[ellenseges-2*meret-2]==1)) szint+=15;
                if ((tabla[ellenseges+meret-1]==1) && (tabla[ellenseges+2*meret-2]==1)) szint+=15;
                if ((tabla[ellenseges-meret+1]==1) && (tabla[ellenseges-2*meret+2]==1)) szint+=15;

                if ((tabla[ellenseges+meret+1]==1) &&  (tabla[ellenseges+meret*2+2]==1) && (tabla[ellenseges+meret*3+3]==1)) szint+=300;
                if ((tabla[ellenseges-meret-1]==1) &&  (tabla[ellenseges-meret*2-2]==1) && (tabla[ellenseges-meret*3-3]==1)) szint+=300;
                if ((tabla[ellenseges+meret-1]==1) &&  (tabla[ellenseges+meret*2-2]==1) && (tabla[ellenseges+meret*3-3]==1)) szint+=300;
                if ((tabla[ellenseges-meret+1]==1) &&  (tabla[ellenseges-meret*2+2]==1) && (tabla[ellenseges-meret*3+3]==1)) szint+=300;

            tablasuly[ellenseges]=szint;
            }


    return tablasuly;
}

void save(unsigned*allas,unsigned*tablasuly,int meret) {
    FILE *f = fopen("save.txt", "w");
    int i,j;
    for (i = 0;i < meret;i++) {
        for (j = 0;j < meret;j++) {
        fprintf(f, "%d", allas[i*meret+j]);

        }
        fprintf(f,"\n");
    }
    fprintf(f,"\n");
    for (i = 0;i < meret;i++) {
        for (j = 0;j < meret;j++) {
            fprintf(f, "%d ", tablasuly[i*meret+j]);
        }
        fprintf(f,"\n");
    }

    fclose(f);
}

void nyert(SDL_Surface*screen ,unsigned*tabla,int meret,int*jatek){
    int i,j;
    int allapot;
        for (i = 0;i < meret;i++)
            for (j = 0;j < meret;j++){
                allapot = i*meret+j;
                if (((tabla[allapot]==1) && (tabla[allapot+1]==1) && (tabla[allapot+2]==1) && (tabla[allapot-1]==1) && (tabla[allapot-2]==1)) || ((tabla[allapot]==1) && (tabla[allapot+meret*1]==1) && (tabla[allapot+meret*2]==1) && (tabla[allapot-meret*1]==1) && (tabla[allapot-meret*2]==1)) || ((tabla[allapot]==1) && (tabla[allapot+meret*1+1]==1) && (tabla[allapot+meret*2+2]==1) && (tabla[allapot-meret*1-1]==1) && (tabla[allapot-meret*2-2]==1)) || ((tabla[allapot]==1) && (tabla[allapot-meret*1+1]==1) && (tabla[allapot-meret*2+2]==1) && (tabla[allapot+meret*1-1]==1) && (tabla[allapot+meret*2-2]==1))) {
                    SDL_FillRect(screen,NULL,0);
                    stringRGBA(screen, 640, 300, "Gratulalunk Nyertel!!", randomszam(0,255), randomszam(0,255), randomszam(0,255), 255);
                    SDL_Flip(screen);
                    SDL_Delay(5000);
                    *jatek = 1;
                    return 0;
                }
                if (((tabla[allapot]==2) && (tabla[allapot+1]==2) && (tabla[allapot+2]==2) && (tabla[allapot-1]==2) && (tabla[allapot-2]==2)) || ((tabla[allapot]==2) && (tabla[allapot+meret*1]==2) && (tabla[allapot+meret*2]==2) && (tabla[allapot-meret*1]==2) && (tabla[allapot-meret*2]==2)) || ((tabla[allapot]==2) && (tabla[allapot+meret*1+1]==2) && (tabla[allapot+meret*2+2]==2) && (tabla[allapot-meret*1-1]==2) && (tabla[allapot-meret*2-2]==2)) || ((tabla[allapot]==2) && (tabla[allapot-meret*1+1]==2) && (tabla[allapot-meret*2+2]==2) && (tabla[allapot+meret*1-1]==2) && (tabla[allapot+meret*2-2]==2))) {
                    SDL_FillRect(screen,NULL,0);
                    stringRGBA(screen, 640, 300, "Gratulalunk Vesztettel!!", randomszam(0,255), randomszam(0,255), randomszam(0,255), 255);
                    SDL_Flip(screen);
                    SDL_Delay(5000);
                    *jatek = 2;
                    return 0;
                }
                }
}

void mentes(unsigned*tabla,int meret,int lepes) {
    FILE *f= fopen("load.txt", "w");
    int i;
    fprintf(f,"%d ",meret);
    fprintf(f,"%d ",lepes);
    for (i=0;i<meret*meret;i++) {
        fprintf(f,"%u ",tabla[i]);
    }
    fclose(f);
}
