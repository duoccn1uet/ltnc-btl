#include "CommonFunc.h"
#include "CreateWindow.h"
#include "Game.h"

using namespace std;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Event event;
string MAP_NAME;

mt19937 rd(chrono :: steady_clock :: now().time_since_epoch().count());

Game game("ninja");

int main(int agrc, char* argv[])
{
    srand(time(0));
    initSDL(window, renderer);
    game.Start();
    ///cout << MAP_NAME;
    ///cout << BACKGROUND_FOLDER << endl;
    ///PlaySound(sound, 1);
   ///Khi thông thường chạy với môi trường bình thường ở nhà
   /// SDL_RenderPresent();
   ///Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
   ///SDL_UpdateWindowSurface(window);
    ///waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
