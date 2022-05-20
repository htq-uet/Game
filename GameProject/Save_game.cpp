
#include "Save_game.h"

using namespace std;

//Read the game level from the file
void Save_game::load_files ()
{

    std::ifstream load ("map/game_save.txt");
    if(!load)
    {
        cout<<"Can't open";
    }

    while(load&&!load.eof() )
    {

        load >> lv;

        load.ignore();

        load.close();
    }
}

//Save the level before exiting the game.
void Save_game:: game_save(int level)
{

    std::ofstream save;
    save.open("map/game_save.txt", std::ofstream::out | std::ofstream::trunc);

    save << level;
    save.close();

    SDL_Quit();
}


