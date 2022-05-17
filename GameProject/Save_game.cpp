
#include "Save_game.h"

using namespace std;

void Save_game::load_files ()
{
    // Open a file for reading
    std::ifstream load ("map/game_save.txt");
    if(!load)
    {
        cout<<"Can't open";
    }
    //If the file loaded
    while(load&&!load.eof() )
    {

    //Read the level
        load >> lv;

        //Skip past the end of line
        load.ignore();

        //Close the file
        load.close();
    }
}

void Save_game:: clean_up(int level)
{

    //Open and clear data inside the file before writing new data
    std::ofstream save;
    save.open("map/game_save.txt", std::ofstream::out | std::ofstream::trunc);

    // Save the level
    save << level;
    //Close the file
    save.close();

    //Quit SDL
    SDL_Quit();
}


