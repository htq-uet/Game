#pragma once

#include "CommonFunction.h"
#include "Player.h"
#include "OtherObj.h"

class Save_game{
    int lv=0;
public:
    void load_files ();
    void clean_up();
    int getLV()
    {
        return lv;
    }
};
