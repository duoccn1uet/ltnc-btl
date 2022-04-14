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

void test()
{
    ImgProcess c;
    c.LoadImg(CHARACTER_FOLDER + "right.png", renderer);
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
        c.Render(renderer, nullptr);
        SDL_RenderPresent(renderer);
    }
}

int main(int agrc, char* argv[])
{
    srand(time(0));
    initSDL(window, renderer);
    ///game.ShowMenu(renderer, FONT_FOLDER + MAP_NAME + OPTION_FONT, MENU_FOLDER + MAP_NAME + "menu.png");
   ///Khi thông thường chạy với môi trường bình thường ở nhà
   /// SDL_RenderPresent(renderer);
   ///Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
   ///SDL_UpdateWindowSurface(window);
   /// waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
