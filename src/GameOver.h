#pragma once
#include "CommonFunction.h"
#include "BaseObj.h"

class GameOver:public BaseObj
{
    public:
        GameOver();
        ~GameOver();

        int loadGameOver(SDL_Renderer* renderer, TTF_Font* font);
        bool CheckFocusWithRectGO(const int& x, const int& y, const SDL_Rect& rect);
        int getCFWR(){ return check;}
        bool isQuit(){ return quit_;}

    private:
        int xp=0;
        int yp=0;
        bool quit_ = false;
        int check;
};



