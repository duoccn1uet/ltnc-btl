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
    game.PlayIntro();
    game.Start();
    /**Threat threat;
    threat.CreateThreat(ThreatType::FLY, ThreatMotionType::FLY);
    ///threat.LoadImg(THREAT_FOLDER+"fly.png");
    threat.SetRect(50, 500);
    Platform g;
    g.LoadPlatform(PlatformType::NORMAL);
    g.SetRect(50, threat.GetRect().y+threat.GetRect().h);
    int t = -1;
    while (true)
    {
        if (SDL_PollEvent(&event) != 0 && event.type == SDL_QUIT)
            return 0;
        SDL_RenderClear(renderer);
        auto rect = threat.GetRect();
        if (rect.x + rect.w > SCREEN_WIDTH)
            threat.ChangeDirection(), threat.MoveLeft(); else
        if (rect.x < 0)
            threat.ChangeDirection(), threat.MoveRight(); else
        if (threat.CurrentMoveType() == ThreatMoveType::LEFT)
            threat.MoveLeft();
        else
            threat.MoveRight();
        threat.Render();
        SDL_RenderPresent(renderer);
        ///SDL_Delay(30);
    }*/
    ///game.Start();
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
