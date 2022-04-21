#include "Game.h"

///#define GAME_DEBUG
#ifndef GAME_DEBUG

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

PlatformType Game :: GenPlatformType()
{
    return PlatformType::NORMAL;
}

/// platforms
void Game :: GenPlatform(int i)
{
    Platform& pl = platforms[i];
    pl.LoadPlatform(GenPlatformType());

    SDL_Rect rect = platforms[i].GetRect();
    SDL_Rect pr_rect = platforms[i-1].GetRect();
    low_y_dist += d_score / DIFFICULTY;
    high_y_dist += d_score / DIFFICULTY;
    mini(high_y_dist, d_JumpHeight-rect.h);
    mini(low_y_dist, high_y_dist);
    
    int y_dist = rand(low_y_dist, high_y_dist);
    rect.y = pr_rect.y - y_dist - rect.h;
    int x_dist = sqrt(SQR_MAX_PLATFOMRS_DIST - y_dist*y_dist);
    rect.x = rand(max(0,pr_rect.x-x_dist), min(pr_rect.x+x_dist, SCREEN_WIDTH-rect.w));
    pl.SetRect(rect.x, rect.y);
}

int Game :: Gen_nplatforms(int cnt)
{
    return rand(cnt, rand(0,7) == 0 ? MAX_PLATFORMS_PER_FRAME : n_platforms);
}

void Game :: InitPlatforms()
{
    n_platforms = rand(MIN_PLATFORMS_PER_FRAME, MAX_PLATFORMS_PER_FRAME);
    for(int i = 0; i < MAX_PLATFORMS_PER_FRAME; ++i)
        has_item[i] = false;
    /// avoid ending the game at the beginning

    platforms[0].LoadPlatform(GenPlatformType());
    SDL_Rect c_rect = character.GetRect();
    platforms[0].SetRect(c_rect.x, c_rect.y + c_rect.h);
    platforms[0].Render();

    for(int i = 1; i < n_platforms; ++i)
        GenPlatform(i);
}

ItemType Game :: GenItemType()
{
    ///return rand(1, 3) == 1 ? ItemType::INVALID : ItemType::COIN;
    return ItemType::COIN;
}

bool Game :: GenItem(int i)
{
    
}

int Game :: Gen_nitems(int cnt)
{
    return rand(cnt, MAX_ITEMS_PER_FRAME);
}

void Game :: InitItems()
{
    for(auto& x : cnt_item)
        x = 0;
}

void Game :: Init()
{
    /// load image for background, character, platforms
    background.LoadImg(BACKGROUND_FOLDER + "background.png");
    character.Init(CHARACTER_FOLDER);
    character.SetRect(SCREEN_WIDTH/2 - character.GetRect().w/2, SCREEN_HEIGHT - character.GetRect().h - 50);
    InitPlatforms();
    InitItems();

    /// init score
    show_score.SetRect(5, 5);
    show_score.SetColor(d_Text_Color::WHITE_TEXT);
    show_score.SetFont(FONT_FOLDER + SCORE_FONT, SCORE_FONT_SIZE);
}

void Game :: ShowScore()
{
    show_score.SetContent("Score: " + to_string(d_score));
    show_score.CreateText();
    show_score.RenderText();
}

int Game :: ScrollMap()
{
    SDL_Rect c_rect = character.GetRect();
    //////cout << c_rect.y << endl;
    if (c_rect.y < SCROLL_LINE)
    {
        int diff = SCROLL_LINE - c_rect.y;
        character.SetRect(c_rect.x, SCROLL_LINE);
        auto ScrollPlatforms = [&]() -> void /// scroll platforms, and gen more
        {
            int cnt = 0;
            for(int i = 0; i < n_platforms; ++i)
            {
                if (platforms[i].GetRect().y+diff < SCREEN_HEIGHT)
                {
                    auto& pl = platforms[cnt];
                    pl = platforms[i];
                    auto p_rect = pl.GetRect();
                    pl.SetRect(p_rect.x, p_rect.y + diff);
                    has_item[cnt] = has_item[i];
                    has_item[i] = false;
                    ++cnt;
                }
            }
            n_platforms = Gen_nplatforms(cnt);
            for(int i = cnt; i < n_platforms; ++i)
                GenPlatform(i);
        };
        auto ScrollItems = [&]() -> void /// scroll items, and gen more
        {
            int cnt = 0;
            for(int i = 0; i < n_items; ++i)
            {
                if (items[i].GetRect().y+diff < SCREEN_HEIGHT)
                {
                    items[cnt] = items[i];
                    auto i_rect = items[cnt].GetRect();
                    items[cnt].SetRect(i_rect.x, i_rect.y+diff);
                    ++cnt;
                }
            }
            n_items = Gen_nitems(cnt);
            ///cout << cnt << ' ' << n_items << ' ';;
            for(int i = cnt; i < n_items; ++i)
                if (GenItem(i) == false)
                {
                    --n_items;
                    --i;
                }
            ///cout << n_items << ' ';
            /**for(int i = 0; i < n_items; ++i)
                if (items[i].GetStatus() != ItemStatus::SHOW)
                    cout << ItemStatusText[uint16_t(items[i].GetStatus())] << endl;*/
            ////cout << n_items << endl;
        };
        
        ScrollPlatforms();
        ScrollItems();
        return diff;
    }
    return 0;
}

void Game :: PlayGame()
{
    Mix_HaltMusic();
    Init();
    bool quit = false;

    int times_per_frame = 1000 / FPS;

    int old_y = character.GetRect().y;

    while (!quit)
    {
        ///timer.Start();
        d_MoveType move_type = d_MoveType::INVALID;
        if (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                quit = true;
            move_type = character.GetMoveType(event);
        }
        if (event.type != SDL_KEYUP)
        {
            auto DoChar = [&]() -> void
            {
                if (!character.Jump())
                {
                    bool jump = false;
                    SDL_Rect cl_rect = character.GetLegsRect();
                    for(int i = 0; i < n_platforms; ++i)
                        if (platforms[i].GetRect().y > cl_rect.y && CheckCollision(platforms[i].GetRect(), cl_rect))
                        {
                            ///cout << i << endl;
                            jump = true;
                            break;
                        }
                    if (jump)
                    {
                        character.d_CurrentMoveType[uint16_t(d_MoveType::JUMP)] = true;
                        character.d_JumpTimes = 0;
                        character.Jump();
                    }
                    else
                        character.Fall();
                }
                character.Cross(move_type);
                character.DoOutOfFrame();
            };
            auto UpdateScore = [&]()
            {
                int current_y = character.GetRect().y;
                if (old_y > current_y)
                {
                    d_score += old_y - current_y;
                    old_y = current_y;
                }
            };
            auto Render = [&]()
            {
                background.Render();
                for(int i = 0; i < n_platforms; ++i)
                    platforms[i].Render();
                int cnt = 0;
                for(int i = 0; i < n_items; ++i)
                {
                    items[i].RenderItem(); 
                    /**ImgProcess p;
                    p.LoadImg(ITEM_FOLDER + "coin_show_0.png");
                    p.SetRect(items[i].GetRect().x, items[i].GetRect().y);
                    p.Render();*/
                    /**if (items[i].GetStatus() != ItemStatus::SHOW)
                        debug(items[i].GetRect().x, items[i].GetRect().y);*/
                        ///cout << ItemStatusText[uint16_t(items[i].GetStatus())] << endl;
                }
                ///cout << cnt << ' ' << n_items << endl;
                ///cout << endl;
                character.Render(); 
                ShowScore();
            };    
            auto CollectItem = [&]() -> void
            {
                
            };
            DoChar();
            old_y += ScrollMap();
            CollectItem();
            UpdateScore();
            Render();
            SDL_RenderPresent(renderer);
        }

        /**int frame_passed = timer.GetTicks();
        int delay_time = times_per_frame - frame_passed;
        if (delay_time > 0)
            SDL_Delay(delay_time);*/
    }
}

/// check if choosen option is home

bool Game :: LoadOption(const MenuOption& option)
{
    if (option == MenuOption::EXIT)
        return false;
    if (option == MenuOption::PLAY)
    {
        PlayGame();
        return false;
    }
    if (option == MenuOption::HELP)
    {
        HelpOption h_option = menu.Help();
        return (h_option == HelpOption::HOME);
    }
}

void Game :: ShowMenu()
{
    LoadSound(menu_sound, SOUND_FOLDER + "menu.mp3");
    PlaySound(menu_sound, INFINITE_LOOP);
    MenuOption m_option = menu.ShowMenu(FONT_FOLDER + OPTION_FONT, MENU_FOLDER + "menu.png");
    bool back_home = LoadOption(m_option);
    while (back_home)
    {
        m_option = menu.ShowMenu();
        back_home = LoadOption(m_option);
    }
}

#else

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

void Game :: Init()
{
    /// load image for background, character, platforms
    background.LoadImg(BACKGROUND_FOLDER + "background.png");
    character.Init(CHARACTER_FOLDER);
    character.SetRect(SCREEN_WIDTH/2 - character.GetRect().w/2, SCREEN_HEIGHT - character.GetRect().h - 50);
    platform.InitPlatforms(PLATFORM_FOLDER + "platform.png", character.GetLegsRect());

    /// load character, platforms for map
    _map.LoadCharacter(&character);
    _map.LoadPlatform(&platform);

    /// init score
    show_score.SetRect(5, 5);
    show_score.SetColor(d_Text_Color::WHITE_TEXT);
    show_score.SetFont(FONT_FOLDER + SCORE_FONT, SCORE_FONT_SIZE);
}

void Game :: ShowScore()
{
    show_score.SetContent("Score: " + to_string(d_score));
    show_score.CreateText();
    show_score.RenderText();
}

void Game :: PlayGame()
{
    Init();
        Mix_HaltMusic();
        bool quit = false;

        int times_per_frame = 1000 / FPS;

        int old_y = character.GetRect().y;

        while (!quit)
        {
            timer.Start();
            d_MoveType move_type = d_MoveType::INVALID;
            if (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_QUIT)
                    quit = true;
                move_type = character.GetMoveType(event);
            }
            if (event.type != SDL_KEYUP)
            {
                background.Render(nullptr);
                character.DoActions(platform, move_type);
                old_y += _map.SrcollMap();
                int current_y = character.GetRect().y;
                if (old_y > current_y)
                {
                    d_score += old_y - current_y;
                    old_y = current_y;
                }
                platform.Render();
                character.Render();
                ShowScore();
                SDL_RenderPresent();
            }

            int frame_passed = timer.GetTicks();
            int delay_time = times_per_frame - frame_passed;
            if (delay_time > 0)
               SDL_Delay(delay_time);
        }
}

/// check if choosen option is home

bool Game :: LoadOption(const MenuOption& option)
{
    if (option == MenuOption::EXIT)
        return false;
    if (option == MenuOption::PLAY)
    {
        PlayGame();
        return false;
    }
    if (option == MenuOption::HELP)
    {
        HelpOption h_option = menu.Help();
        return (h_option == HelpOption::HOME);
    }
}

void Game :: ShowMenu(const string& font_path, const string& menu_path)
{
    LoadSound(menu_sound, SOUND_FOLDER + "menu.mp3");
    PlaySound(menu_sound, INFINITE_LOOP);
    /**MenuOption option = menu.ShowMenu(font_path, menu_path);
    LoadOption(option, font_path, menu_path);*/
    MenuOption m_option = menu.ShowMenu(font_path, menu_path);
    bool back_home = LoadOption(m_option);
    while (back_home)
    {
        m_option = menu.ShowMenu();
        back_home = LoadOption(m_option);
    }
}

#endif /// GAME_DEBUG
