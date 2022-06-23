#include "CommonFunc.h"
#include "CreateWindow.h"
#include "Game.h"

using namespace std;

/// Folder
string BACKGROUND_FOLDER;
string CHARACTER_FOLDER;
string PLATFORM_FOLDER;
string FONT_FOLDER;
string SOUND_FOLDER;
string MENU_FOLDER;
string OPTION_FOLDER;
string ITEM_FOLDER;
string THREAT_FOLDER;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
SDL_Event event;
string MAP_NAME;

mt19937 rd(chrono ::steady_clock ::now().time_since_epoch().count());

Game game("ninja");

int main(int agrc, char *argv[])
{
    srand(time(0));
    initSDL(window, renderer);  
    game.PlayIntro();
    game.Start();
    /// waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
