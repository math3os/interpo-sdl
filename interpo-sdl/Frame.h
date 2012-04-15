

#ifndef _FRAME_H
#define _FRAME_H
#include <SDL/SDL.h>
#include "libsdl.h"
#include "interpoApp.h"
namespace interpo{

class Frame
{

    public:
        Frame();
        ~Frame();
        SDL_Surface*   screen;

    void                start();

    protected:

    private:
    //SDL_Event* event;
    bool                running;
    const static        int Frame_L = 900;
    const static        int Frame_H = 700;
    //libsdl lib(int Frame_L,int Frame_H);
    SDL_Surface         *workspace;  //espace de dessin
    SDL_Rect            rec_work;
    libsdl              lib;   //InitialiseFenetresdl
    SDL_Surface*        button[10];
    SDL_Rect            posButton[10];
    void                OnLButtonup(int x,int y);
    void                OnLButtonDown(int x,int y);
    void                switchButtonImg(int i,bool state);
    void                buttonAction(int i);
    int                 debug;
    interpoApp          app;
    Val *               pt;
    int                 wrkYMax;
    int                 wrkXMax;
    int                 wrkXPas;
    int                 wrkYPas;

};
}
#endif // FRAME_H
