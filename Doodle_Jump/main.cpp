#include "CommonFunc.h"
#include "Game.h"

#define background game.background
#define character game.character
#define platform game.platform
#define _map game._map
#define timer game.timer
#define MAP_NAME game.MAP_NAME
#define show_score game.show_score
#define menu game.menu

using namespace std;

Game game("");

int main(int agrc, char* argv[])
{
    srand(time(0));
    initSDL(window, renderer);
    game.ShowMenu(renderer, FONT_FOLDER + MAP_NAME + OPTION_FONT, MENU_FOLDER + MAP_NAME + "menu.png");
   ///Khi thông thường chạy với môi trường bình thường ở nhà
   /// SDL_RenderPresent(renderer);
   ///Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
   ///SDL_UpdateWindowSurface(window);
   /// waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
