int jatek_meret(SDL_Surface* screen);
/**< A jatek meretenek kivalasztasa */

void boxrajz(SDL_Surface* screen,int meret);
/**< Jatek meretenek kivalasztasanak doboza */

unsigned* jatek_init(int meret);
/**< Tabla inicialasa */

int jatek_start(SDL_Surface* screen,int meret,unsigned* tabla,int toltes,int lepes);
/**< Jatek inditasa, ettol kezdve folyamatosan megy a jatek */

void tablarajz(SDL_Surface* screen,int meret, unsigned* tabla);
/**< Kirajzolja a tablat */

void mozgas(SDL_Surface* screen,int x,int y);
/**< A kis kor mozgatasa, hogy hova rakja */

int geprak(SDL_Surface* screen,unsigned* tabla,int meret);
/**< Kivalasztja a gep hogy hova rakjon a scannelt tabla ertekei alapjan */

unsigned* tablascan(unsigned* tabla,int meret);
/**< Atscanneli az egesz tablat ertekeket adva azoknak a mezoknek ahol lehetseges veszely lehet */

void save(unsigned*allas,unsigned*tablasuly,int meret);
/**< Csina egy mentest az aktualis tablarol és a sulyzott tablarol */

void nyert(SDL_Surface*screen ,unsigned*tabla,int meret,int* jatek);
/**< Annak vizsgalata hogy nyert-e valaki */

void mentes(unsigned*tabla,int meret,int lepes);
/**< Az "s" betu megnyomasaval elmentese az aktualis tablanak*/
