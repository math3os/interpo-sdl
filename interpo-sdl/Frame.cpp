//Utilise libsdl pour dessiner la fenêtre


#include "Frame.h"
#include "libsdl.h"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

using namespace std;
namespace interpo
{
typedef struct {
    int x;
    int y;
} Point;



Frame::Frame() : lib(Frame_L,Frame_H,lib.couleurs[C_GRIS])  //2fois lameme couleur oh?
{
    debug =1;
    text = NULL;
    screen = lib.getScreen(); //bientot deprecate


    rec_work.h = (Frame_H)/5*4;
    rec_work.w = (Frame_L)/5*4;
    rec_work.x=10;
    rec_work.y=10;

    rec_text.h= (Frame_H)/5 -100;
    rec_text.w = rec_work.w ;
    rec_text.x= rec_work.x;
    rec_text.y = rec_work.h+ rec_work.y +8;
    workspace = SDL_CreateRGBSurface(SDL_SWSURFACE,rec_work.w,rec_work.h,32,0,0,0,0 );
    textZone =  SDL_CreateRGBSurface(SDL_SWSURFACE,rec_text.w,rec_text.h,32,0,0,0,0 );

    txt.cfg = {0,0,0};
    txt.cbg = {0xFF,0xFF,0xFF};
    txt.s = 16;
    txt.t = "Hello World";
    txt.dRect.x=  50;
    txt.dRect.y=  20;


    if(!(txt.f=TTF_OpenFont("ttf/FreeSerif.ttf",txt.s))) printf("TTF_Openfont : %s\n",TTF_GetError());

    SDL_FillRect(screen, 0, lib.couleurs[C_GRIS]);

txt.d = textZone;
    if(workspace == NULL)
      exit(12);

    SDL_FillRect(workspace,0 , SDL_MapRGB(screen->format, 255, 255, 255));
    SDL_FillRect(textZone ,0 , SDL_MapRGB(screen->format, 255, 255, 255));
    running = true;
    drawTextZone(&txt);


    for(int i=0; i<10; i++) {
        posButton[i].x = (Frame_L - (rec_work.w+rec_work.x))/2 + rec_work.w +  rec_work.x- 50 ;
        posButton[i].y = 10+ (50 * i);
        button[i]= NULL;
    }

    button[0] = SDL_LoadBMP("img/bn-init-on.bmp");
    button[1] = SDL_LoadBMP("img/bn-interpo1-on.bmp");




}


Frame::~Frame() {

TTF_CloseFont(font);
}



void Frame::drawTextZone(TextZone *txt){
   SDL_FillRect(textZone  ,0 , SDL_MapRGB(screen->format, 255, 255, 255));
    if(!(txt->surf=TTF_RenderText_Shaded(txt->f,txt->t.c_str(),txt->cfg,txt->cbg)))printf("renderError : %s\n",TTF_GetError());
    //const char* text = txt->t.c_str();

     SDL_BlitSurface(txt->surf,0,txt->d,&txt->dRect);

}

void Frame::drawWorkSpace(){ //remplit/efface la zone de points
    SDL_FillRect(workspace,0 , SDL_MapRGB(screen->format, 255, 255, 255));
    //plus de détails peuvent etre ajouté comme une grille et une échelle
}
void Frame::drawNuage(){
 pt = app.openFile(); //obtenir la liste;
        Val *ptStart = pt;
        wrkXMax = app.getNbVals(); //X max
        wrkYMax = 1;
        for (int i=0; i< wrkXMax; i++) { // y max
            if (pt->y > wrkYMax) {
                wrkYMax = pt->y;
                if(debug)printf("plusgrand = %d\n",wrkYMax);
            }
            printf("wrkYMax = %d\n", wrkYMax);
            pt++;
        }
        pt = ptStart;
        // printf("ici\n");

        wrkXPas = rec_work.w / wrkXMax;   // les 2 pas
        wrkYPas = rec_work.h /wrkYMax;

        unsigned int x;
        unsigned int y;

        if ( SDL_MUSTLOCK(screen) ) {
            if ( SDL_LockSurface(workspace) < 0 ) {
                printf( "Can't lock screen: %s\n", SDL_GetError());
                return;
            }
        }

        for (int i=0; i< wrkXMax; i++) {

            x= pt->x*wrkXPas+rec_work.x-2;
            y= rec_work.h-(pt->y*wrkYPas)-2;
            printf("i = %d\t x = %d \t y = %d\n",i,x,y);
            lib.point(workspace,x , y, lib.couleurs[C_BLEU]);
            pt++;
        }
        if ( SDL_MUSTLOCK(workspace) ) SDL_UnlockSurface(workspace);
        printf("workspace coords : x:%d,%d\t y: %d,%d\n",rec_work.x,rec_work.x+rec_work.w,rec_work.y,rec_work.y+rec_work.h);
        SDL_UpdateRect(workspace,0,0,0,0);
}

void    Frame::start()
{

    drawWorkSpace();
    int done =0;
    while (!done ) {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // check for messages
            switch (event.type)      {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:                {
                // exit if ESCAPE is pressed
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                break;
            }
            case SDL_MOUSEBUTTONDOWN:             {
                switch(event.button.button) {
                case SDL_BUTTON_LEFT: {
                    if(debug) printf("mouse click catched");
                    OnLButtonDown(event.button.x,event.button.y);
                    break;
                }
                }
                break;
            }

            case SDL_MOUSEBUTTONUP:             {
                switch(event.button.button) {
                case SDL_BUTTON_LEFT: {
                    if(debug) printf("mouse click done catched");
                    OnLButtonup(event.button.x,event.button.y);
                    printf("finlbutonup" );
                    break;
                }
                //printf("fin switch 1\n" );
                }
                break;
                printf("fin case mouse \n" );
            }

            //Gadget : zoom avec la molette



            } // end switch
        } // end of message processing

        // DRAWING STARTS HERE

        // clear screen

        SDL_BlitSurface(workspace,NULL,screen,&rec_work);
        SDL_BlitSurface(textZone,NULL,screen,&rec_text);
        for(int i=0; i<10; i++) { //colle les boutons
            if(button[i]) SDL_BlitSurface(button[i],0,screen,&posButton[i]);
        }


        // draw bitmap
        //SDL_BlitSurface(bmp, 0, screen, &dstrect);

        // DRAWING ENDS HERE

        // finally, update the screen :)
        SDL_Flip(screen);
    } // end main loop}
}

void Frame::OnLButtonDown(int x,int y)
{
    if(debug) printf("\n x = %d, y = %d\n",x,y);
    for(int i=0; i<10; i++) {
        if(button[i]) {
            if(x > posButton[i].x && x < posButton[i].x+button[i]->clip_rect.w
                    && y > posButton[i].y && y < posButton[i].y+button[i]->clip_rect.h
              ) {
                if(debug) printf("\nbutton click catched\n");
                switchButtonImg(i,true) ;

                break;
            } else if(debug) printf("début du bouton :  (%d,%d), fin : (%d,%d)\n",posButton[i].x, posButton[i].y,
                                        posButton[i].x+button[i]->clip_rect.w,posButton[i].y+button[i]->clip_rect.h);

        }
    }

}

void Frame::OnLButtonup(int x,int y)
{
    for(int i=0; i<10; i++) {
        if(button[i]) {
            if(x > posButton[i].x && x < posButton[i].x+button[i]->clip_rect.w
                    && y > posButton[i].y&& y < posButton[i].y+button[i]->clip_rect.h
              ) {
                switchButtonImg(i,false) ;
                buttonAction(i) ;
                printf( "ONLButton");
                break;
            }
        }
    }
}
void Frame::switchButtonImg(int i,bool state)
{
    switch(i) {
    case 0: {
        if(!state) button[0] = SDL_LoadBMP("img/bn-init-on.bmp");
        else button[0] = SDL_LoadBMP("img/bn-init-off.bmp");
        SDL_UpdateRect(button[0],0,0,0,0);
        break;
    }
    case 1: {
        if(!state) button[1] = SDL_LoadBMP("img/bn-interpo1-on.bmp");
        else button[1] = SDL_LoadBMP("img/bn-interpo1-off.bmp");
        SDL_UpdateRect(button[1],0,0,0,0);
        break;
    }

    }
}

void Frame::buttonAction(int i) //dessine le nuage de point
{
    switch(i) {
    case 0: {
       drawNuage();
        break;
    }
    case 1:
        txt.t ="Voici mon nouveau Texte!!";
        drawTextZone(&txt);
        break;
    case 2:
        break;


    }

}
}
