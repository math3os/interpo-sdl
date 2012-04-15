//Les widgets de la fenêtre

#include <iostream>
#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "libsdl.h"
#include <SDL/SDL_ttf.h>


namespace interpo{

SDL_Surface*    libsdl::getScreen(){return affichage;}


libsdl::libsdl(int W,int H,Uint32 coul){
	//initSDL(W,H, coul);

	 if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

    //TTF things
	font = NULL;
	if(TTF_Init() == -1)       {
            fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
            exit(EXIT_FAILURE);
    }

    initCouleurs();
}


libsdl::~libsdl(){
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}


void libsdl::initSDL(SDL_surface *s,int W,int H, Uint32 coul,string topic="SMG-libSDL | Par Mathieu Gagnon")
//avec surface
{
  s = SDL_SetVideoMode(W, H, 32, SDL_SWSURFACE);

  if (affichage == NULL) {
    fprintf(stderr, "Impossible d'activer le mode graphique : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_WM_SetCaption("TP 3-4, Interpolation par Mathieu Gagnon et Evans Girards", NULL);
}

void libsdl::initSDL(int W,int H, Uint32 coul,string topic="SMG-libSDL | Par Mathieu Gagnon")
//sans surface
{
  affichage = SDL_SetVideoMode(W, H, 32, SDL_SWSURFACE);

  if (affichage == NULL) {
    fprintf(stderr, "Impossible d'activer le mode graphique : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  SDL_WM_SetCaption("TP 3-4, Interpolation par Mathieu Gagnon et Evans Girards", NULL);
}


void    libsdl::initCouleurs(void)
{
  couleurs[C_NOIR]        		= SDL_MapRGB(affichage->format, 0x00, 0x00, 0x00);
  couleurs[C_BLEU_FONCE]	  	= SDL_MapRGB(affichage->format, 0x00, 0x00, 0x80);
  couleurs[C_VERT_FONCE]		= SDL_MapRGB(affichage->format, 0x00, 0x80, 0x00);
  couleurs[C_CYAN_FONCE]    	= SDL_MapRGB(affichage->format, 0x00, 0x80, 0x80);
  couleurs[C_ROUGE_FONCE]   	= SDL_MapRGB(affichage->format, 0x80, 0x00, 0x00);
  couleurs[C_MAGENTA_FONCE] 	= SDL_MapRGB(affichage->format, 0x80, 0x00, 0x80);
  couleurs[C_OCRE]          	= SDL_MapRGB(affichage->format, 0x80, 0x80, 0x00);
  couleurs[C_GRIS_CLAIR]    	= SDL_MapRGB(affichage->format, 0xC0, 0xC0, 0xC0);
  couleurs[C_GRIS]          	= SDL_MapRGB(affichage->format, 0x80, 0x80, 0x80);
  couleurs[C_BLEU]        	  	= SDL_MapRGB(affichage->format, 0x00, 0x00, 0xFF);
  couleurs[C_VERT]          	= SDL_MapRGB(affichage->format, 0x00, 0xFF, 0x00);
  couleurs[C_CYAN]          	= SDL_MapRGB(affichage->format, 0x00, 0xFF, 0xFF);
  couleurs[C_ROUGE]         	= SDL_MapRGB(affichage->format, 0xFF, 0x00, 0x00);
  couleurs[C_MAGENTA]       	= SDL_MapRGB(affichage->format, 0xFF, 0x00, 0xFF);
  couleurs[C_JAUNE]         	= SDL_MapRGB(affichage->format, 0xFF, 0xFF, 0x00);
  couleurs[C_BLANC]         	= SDL_MapRGB(affichage->format, 0xFF, 0xFF, 0xFF);
}


void libsdl::setPixel(SDL_Surface * w, int x, int y, Uint32 coul){
     *((Uint32*)(w->pixels) + x + y * w->w) = coul; }

void libsdl::setPixelVerif(SDL_Surface* w, int x, int y, Uint32 coul){
  if (x >= 0 && x < w->w &&
      y >= 0 && y < w->h)
    setPixel(w,x, y, coul);
}

void libsdl::setPixelVerif(int x, int y, Uint32 coul)
{
  if (x >= 0 && x < affichage->w &&
      y >= 0 && y < affichage->h)
    setPixel(affichage,x, y, coul);
}

void libsdl::barre(int x, int y, int w, int h, Uint32 coul)
{
  SDL_Rect r;
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;

  SDL_FillRect(affichage, &r, coul);
}

void libsdl::ligneHorizontale(int x, int y, int w, Uint32 coul)
{
  SDL_Rect r;
  r.x = x;  r.y = y;  r.w = w;  r.h = 1;
  SDL_FillRect(affichage, &r, coul);
}

void libsdl::point(SDL_Surface *s,int x, int y, Uint32 coul){
    int size = 3;
    for (int i=0;i<size;i++){

        for(int j =0; j < size;j++)

            setPixel(s,x+i-1,y+j-1,coul);

          }
    }


void libsdl::ligne(int x1, int y1, int x2, int y2, Uint32 coul)
//anomaly.developpez.com
{
  int d, dx, dy, aincr, bincr, xincr, yincr, x, y;

  if (abs(x2 - x1) < abs(y2 - y1)) {
    /* parcours par l'axe vertical */

    if (y1 > y2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }

    xincr = x2 > x1 ? 1 : -1;
    dy = y2 - y1;
    dx = abs(x2 - x1);
    d = 2 * dx - dy;
    aincr = 2 * (dx - dy);
    bincr = 2 * dx;
    x = x1;
    y = y1;

    setPixelVerif(x, y, coul);

    for (y = y1+1; y <= y2; ++y) {
      if (d >= 0) {
	x += xincr;
	d += aincr;
      } else
	d += bincr;

      setPixelVerif(x, y, coul);
    }

  } else {
    /* parcours par l'axe horizontal */

    if (x1 > x2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }

    yincr = y2 > y1 ? 1 : -1;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    d = 2 * dy - dx;
    aincr = 2 * (dy - dx);
    bincr = 2 * dy;
    x = x1;
    y = y1;

    setPixelVerif(x, y, coul);

    for (x = x1+1; x <= x2; ++x) {
      if (d >= 0) {
	y += yincr;
	d += aincr;
      } else
	d += bincr;

      setPixelVerif(x, y, coul);
    }
  }
}

void libsdl::ligneVerticale(int x, int y, int h, Uint32 coul)
{
  SDL_Rect r;
  r.x = x;  r.y = y;  r.w = 1;  r.h = h;
  SDL_FillRect(affichage, &r, coul);
}
void libsdl::echangerEntiers(int* x, int* y)
{
  int t = *x; *x = *y; *y = t;
}
void libsdl::putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }

}


//	if(!(text=TTF_RenderUTF8_Solid(font,"Hello World!",noir))) {
//		printf("TTF_Init: %s\n", TTF_GetError());
//		exit(2);
//	} else {
	//SDL_BlitSurface(text,NULL,affichage,&pos);
    //perhaps we can reuse it, but I assume not for simplicity.


	//TTF_RenderUTF8_Solid(font,"hello world",noir);

}//fin namespace interpo


