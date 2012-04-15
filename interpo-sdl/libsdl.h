
//prototypes
#ifndef LIBSDL_H_INTERPO
#define LIBSDL_H_INTERPO
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


namespace interpo{
    enum {
  C_NOIR, C_BLEU_FONCE, C_VERT_FONCE, C_CYAN_FONCE, C_ROUGE_FONCE,
  C_MAGENTA_FONCE, C_OCRE, C_GRIS_CLAIR, C_GRIS, C_BLEU, C_VERT,
  C_CYAN, C_ROUGE, C_MAGENTA, C_JAUNE, C_BLANC,

  NB_COULEURS
  };
class libsdl {

public:
	libsdl(int W=900,int H=700, Uint32 coul=0); //charge SDL

	~libsdl();

  void              ligneVerticale(int x, int y, int h, Uint32 coul);
  void              ligneHorizontale(int x, int y, int w, Uint32 coul);
  void              barre(int x, int y, int w, int h, Uint32 coul);
  //SDL_Surface*      setWorkspace(SDL_Surface *workspace,SDL_Rect rect_work,Uint32 coul);
  SDL_Surface*      getScreen();

  Uint32          couleurs[NB_COULEURS];

  void            ligne(int x1, int y1, int x2, int y2, Uint32 coul);
  void            putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
  void            point(SDL_Surface *s,int x, int y, Uint32 coul);
//void initFont(SDL_Surface *text);

private:
    void        initSDL (int W,int H, Uint32 coul);
    void        initCouleurs(void);
    void        setPixel(SDL_Surface *w,int x, int y, Uint32 coul);
    void        setPixelVerif(SDL_Surface *w, int x, int y, Uint32 coul);
    void        setPixelVerif(int x, int y, Uint32 coul);
    TTF_Font    *font;
    void        initFont(SDL_Surface *text);
    SDL_Color   noir;


    void        echangerEntiers(int* x, int* y);
    SDL_Surface *affichage;

};
}

#endif
