#include "Game.h"

Game :: Game()
{

}

Game :: Game(const string& _MAP_NAME)
{
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << '\n';

     //Initialize SDL_ttf
    if(TTF_Init() == -1)
        cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << '\n';

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << '\n';

    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << '\n';
    MAP_NAME = _MAP_NAME;

}

Game :: ~Game()
{
    Mix_FreeMusic(menu_sound);
}

void Game :: Init(SDL_Renderer* renderer)
{
    /// load image for background, character, platforms
    background.LoadImg(BACKGROUND_FOLDER + MAP_NAME + "background.png", renderer);
    character.Init(renderer, CHARACTER_FOLDER + MAP_NAME);
    character.SetRect(SCREEN_WIDTH/2 - character.GetRect().w/2, SCREEN_HEIGHT - character.GetRect().h - 50);
    platform.InitPlatforms(renderer, PLATFORM_FOLDER + MAP_NAME + "platform.png", character.GetLegsRect());

    /// load character, platforms for map
    _map.LoadCharacter(&character);
    _map.LoadPlatform(&platform);

    /// init score
    show_score.SetRect(5, 5);
    show_score.SetColor(d_Text_Color::WHITE_TEXT);
    show_score.SetFont(FONT_FOLDER + MAP_NAME + SCORE_FONT, SCORE_FONT_SIZE);
}

void Game :: ShowScore(SDL_Renderer* renderer)
{
    show_score.SetContent("Score: 123456789");
    show_score.CreateText(renderer);
    show_score.RenderText(renderer);
}

void Game :: LoadOption(SDL_Renderer* renderer, const MenuOption& option, const string& font_path, const string& menu_path)
{
    if (option == MenuOption::EXIT)
        return;
    if (option == MenuOption::PLAY)
    {
        Init(renderer);
        Mix_HaltMusic();
        bool quit = false;

        int times_per_frame = 1000 / FPS;

        while (!quit)
        {
            timer.Start();
            d_MoveType move_type = d_MoveType::INVALID;
            while (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_QUIT)
                    quit = true;
                move_type = character.GetMoveType(event);
            }
            if (event.type != SDL_KEYUP)
            {
                background.Render(renderer, nullptr);
                character.DoActions(platform, move_type);
                _map.SrcollMap();
                platform.Render(renderer);
                character.Render(renderer);
                ShowScore(renderer);
                SDL_RenderPresent(renderer);
            }

            int frame_passed = timer.GetTicks();
            int delay_time = times_per_frame - frame_passed;
            ///if (delay_time > 0)
            ///    SDL_Delay(delay_time);
        }
    }
    if (option == MenuOption::HELP)
    {
        HelpOption h_option = menu.Help(MAP_NAME, renderer);
        if (h_option == HelpOption::HOME)
        {
            MenuOption option = menu.ShowMenu(renderer, font_path, menu_path);
            LoadOption(renderer, option, font_path, menu_path);
        }
    }
}

void Game :: ShowMenu(SDL_Renderer* renderer, const string& font_path, const string& menu_path)
{
    LoadSound(menu_sound, SOUND_FOLDER + MAP_NAME + "menu.mp3");
    PlaySound(menu_sound, INFINITE_LOOP);
    MenuOption option = menu.ShowMenu(renderer, font_path, menu_path);
    LoadOption(renderer, option, font_path, menu_path);
}
