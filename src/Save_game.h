
#pragma once

#include "CommonFunction.h"
#include "fstream"

class Save_game{
    int lv=1;
public:
    void load_files ();
    void game_save(int level);
    int getLV()
    {
        return lv;
    }
};
