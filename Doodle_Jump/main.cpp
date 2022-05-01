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

void test()
{
    ImgProcess c;
    c.LoadImg(CHARACTER_FOLDER + "right.png");
    int x = 100, y = 100;
    SDL_Event e;
    int deltaX = 5;
    while (true)
    {
        if (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                return;
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        x += deltaX;
                        break;
                    case SDLK_LEFT:
                        x -= deltaX;
                }
            }
        }
        c.SetRect(x, y);
        SDL_RenderClear(renderer);
        c.Render(nullptr);
        SDL_RenderPresent(renderer);
    }
}

int main(int agrc, char* argv[])
{
    srand(time(0));
    initSDL(window, renderer);
    game.ShowMenu();
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
