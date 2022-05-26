#include "Game.h"

///#define GAME_DEBUG
#ifndef GAME_DEBUG

vector <Option> options;
const int HardnessValue[] = {3/ PIXEL_PER_SCORE, 400 / PIXEL_PER_SCORE, 100 / PIXEL_PER_SCORE};
int DIFFICULTY = HardnessValue[0];
/// score
const int NUMBER_OF_HIGH_SCORES = 6;
set <int, greater <int>> high_scores;

/// Threat
vector <ImgProcess> ThreatsImg;

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

    BACKGROUND_FOLDER = MAP_NAME + "\\img\\background\\";
    CHARACTER_FOLDER = MAP_NAME + "\\img\\character\\";
    PLATFORM_FOLDER = MAP_NAME + "\\img\\platform\\";
    FONT_FOLDER = MAP_NAME + "\\font\\";
    SOUND_FOLDER = MAP_NAME + "\\sound\\";
    MENU_FOLDER = MAP_NAME + "\\img\\menu\\";
    OPTION_FOLDER = MAP_NAME + "\\img\\option\\";
    ITEM_FOLDER = MAP_NAME + "\\img\\item\\";
    THREAT_FOLDER = MAP_NAME + "\\img\\threat\\";
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
    low_y_dist = 20 + d_score / DIFFICULTY;
    high_y_dist = d_JumpHeight/5 + d_score / DIFFICULTY;
    mini(high_y_dist, d_JumpHeight-rect.h-character.GetLegsRect().h);
    mini(low_y_dist, high_y_dist);
    
    int y_dist = rand(low_y_dist, high_y_dist);
    rect.y = pr_rect.y - y_dist - rect.h;
    int x_dist = sqrt(SQR_MAX_PLATFOMRS_DIST - y_dist*y_dist);
    rect.x = rand(max(0,pr_rect.x-x_dist), min(pr_rect.x+x_dist, SCREEN_WIDTH-rect.w));
    pl.SetRect(rect.x, rect.y);
}

int Game :: Gen_nplatforms()
{
    return rand(n_platforms, rand(0,7) == 0 ? MAX_PLATFORMS_PER_FRAME : n_platforms);
}

void Game :: InitPlatforms()
{
    n_platforms = rand(MIN_PLATFORMS_PER_FRAME, MAX_PLATFORMS_PER_FRAME);
    /// avoid ending the game at the beginning

    platforms[0].LoadPlatform(PlatformType::NORMAL);
    SDL_Rect c_rect = character.GetRect();
    platforms[0].SetRect(c_rect.x, c_rect.y + c_rect.h);
    platforms[0].Render();

    for(int i = 1; i < n_platforms; ++i)
        GenPlatform(i);
}

ItemType Game :: GenItemType()
{
    ///return rand(1, 3) == 1 ? ItemType::INVALID : ItemType::COIN;
    vector <int> cnt_type(etoi(ItemType::nItemType));
    for(int i = 0; i < n_items; ++i)
        ++cnt_type[etoi(items[i].GetType())];
    vector <int> v(etoi(ItemType::nItemType));
    iota(all(v), 0);
    shuffle(all(v), rd);
    for(int item_type : v)
        if (cnt_type[item_type] < MAX_ITEM_TYPE_PER_FRAME[item_type])
            return static_cast <ItemType> (item_type);
    return ItemType::INVALID;
}

bool Game :: GenItem(int i)
{
    ItemType type = GenItemType();
    if (type == ItemType::INVALID)
        return false;
    vector <int> id;
    for(int j = highest_free_platform; j < n_platforms-1; ++j)
        if (platforms[j].GetRect().y < 0)
            id.eb(j);
    if (id.empty())
        return false;
    shuffle(all(id), rd);
    Item& item = items[i];
    item.SetItem(type, ItemStatus::SHOW);
    SDL_Rect i_rect = item.GetRect();
    for(int j : id)
    {
        SDL_Rect p_rect = platforms[j].GetRect();
        if (platforms[j+1].GetRect().y + platforms[j+1].GetRect().h + i_rect.h < p_rect.y)
        {
            int x = rand(p_rect.x, p_rect.x + p_rect.w - i_rect.w);
            int y = p_rect.y - i_rect.h + 2;
            item.SetRect(x, y);
            highest_free_platform = j+1;
            return true;
        }
    }
    return false;
}

int Game :: Gen_nitems()
{
    return rand(n_items, MAX_ITEMS_PER_FRAME);
}

void Game :: InitItems()
{
    for(auto& x : cnt_item)
        x = 0;
}

ThreatType Game :: GenThreatType()
{
    return ThreatType::JUMP;
    vector <int> cnt_type(etoi(ThreatType::nThreatType));
    for(int i = 0; i < n_threats; ++i)
        ++cnt_type[etoi(threats[i].GetType())];
    vector <int> v(etoi(ThreatType::nThreatType));
    iota(all(v), 0);
    shuffle(all(v), rd);
    for(int threat_type : v)
        if (cnt_type[threat_type] < MAX_THREAT_TYPE_PER_FRAME[threat_type])
            return static_cast <ThreatType> (threat_type);
    return ThreatType::INVALID;
}

bool Game :: GenThreat(int i)
{
    ThreatType t_type = GenThreatType();
    if (t_type == ThreatType::INVALID)
        return false;
    vector <int> id;
    for(int j = highest_free_platform; j < n_platforms-1; ++j)
        if (platforms[j].GetRect().y < 0)
            id.eb(j);
    if (id.empty())
        return false;
    shuffle(all(id), rd);
    Threat& threat = threats[i];
    threat.SetThreatType(t_type);
    threat.SetMotionType(threat.GetDefaultMotionType());
    SDL_Rect t_rect = threat.GetRect();
    for(int j : id)
    {
        SDL_Rect p_rect = platforms[j].GetRect();
        int above_bound = platforms[j+1].GetRect().y + platforms[j+1].GetRect().h;
        if (above_bound + 1.5*t_rect.h < p_rect.y)
        {
            highest_free_platform = j+1;
            switch (t_type)
            {
                case ThreatType::FLY:
                    threat.SetRect(0, rand(above_bound+5, p_rect.y-t_rect.h-5));
                    break;

                case ThreatType::JUMP:
                    threat.SetRect(rand(p_rect.x, p_rect.x+p_rect.w-t_rect.w), p_rect.y-t_rect.h);
                    ///debug(p_rect.y, threat.GetRect().y + threat.GetRect().h);
                    break;

                case ThreatType::MOVE_ON_PLATFORM:
                    threat.SetRect(rand(p_rect.x, p_rect.x+p_rect.w-t_rect.w), p_rect.y-t_rect.h);
                    break;
            }
            return true;
        }
    }
    return false;
}

int Game :: Gen_nThreats()
{
    return rand(n_threats, MAX_THREATS_PER_FRAME);
}

void Game :: InitThreats()
{
    for(auto& x : cnt_threat)
        x = 0;
}

void Game :: InitOptions()
{
    options.resize(etoi(OPTION::nOPTION));
    for(int i = 0; i < options.size(); ++i)
    {
        options[i].CreateOption(static_cast <OPTION>(i));
    }
}

void Game :: Init()
{
    /// load image for background, character, platforms
    background.LoadImg(BACKGROUND_FOLDER + "background.png");
    top_frame.LoadImg(BACKGROUND_FOLDER + "top_frame.png");
    character.SetRect(SCREEN_WIDTH/2 - character.GetRect().w/2, SCREEN_HEIGHT - character.GetRect().h - 50);
    InitPlatforms();
    InitItems();
    InitThreats();

    /// init score
    d_score = 0;
    show_score.SetRect(5, 2);
    show_score.SetColor(d_Text_Color::BLACK_TEXT);
    show_score.SetFont(FONT_FOLDER + SCORE_FONT, SCORE_FONT_SIZE);
    ///show_score.SetFontSType(TTF_STYLE_BOLD);

    /// Load options
    for(int i = 0; i < InGameOptions.size(); ++i)
    {
        int id = etoi(InGameOptions[i]);
        options[id].SetRect(InGameOptionsX[i], InGameOptionsY[i]);
    }
    in_game_options_pack.resize(etoi(InGameOptionsPack::nInGameOptionsPack));
    for(int i = 0; i < in_game_options_pack.size(); ++i)
    {
        in_game_options_pack[i].background.LoadImg(BACKGROUND_FOLDER + InGameOptionsPackText[i] + ".png");
        in_game_options_pack[i].header_name.CreateText(OPTION_FONT, OPTION_FONT_SIZE, InGameOptionsPackText[i], d_Text_Color::BLACK_TEXT);
        in_game_options_pack[i].SetRect(InGameOptionsPackX[i], InGameOptionsPackY[i]);
        for(OPTION o : OptionsInInGameOptionsPack[i])
            in_game_options_pack[i].AddOption(o);
    }
}

void Game :: ShowScore()
{
    show_score.SetContent("Score: " + to_string(d_score));
    show_score.CreateText();
    show_score.Render();
}

int Game :: ScrollMap()
{
    SDL_Rect c_rect = character.GetRect();
    //////cout << c_rect.y << endl;
    if (c_rect.y < SCROLL_LINE)
    {
        int diff = SCROLL_LINE - c_rect.y;
        character.SetRect(c_rect.x, SCROLL_LINE);
        auto ScrollBackground = [&]() -> void
        {   
            background.SetRect(0, background.GetRect().y + diff);
            auto rect = background.GetRect();
            if (rect.y > SCREEN_HEIGHT)
            {
                rect.y -= SCREEN_HEIGHT;
                background.SetRect(0, rect.y);
            }
        };
        auto ScrollPlatforms = [&]() -> void /// scroll platforms
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
                    ++cnt;
                }
            }
            ///for(int i = cnt; i < n_platforms; ++i)
            ///    platforms[i].FreePlatform();
            highest_free_platform -= n_platforms - cnt;
            n_platforms = cnt;
        };
        auto ScrollItems = [&]() -> void /// scroll items
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
            for(int i = cnt; i < n_items; ++i)
                items[i].FreeItem();
            n_items = cnt;
        };
        auto ScrollThreats = [&]() -> void // scroll threats
        {
            int cnt = 0;
            for(int i = 0; i < n_threats; ++i)
            {
                if (threats[i].GetRect().y+diff < SCREEN_HEIGHT)
                {
                    threats[cnt] = threats[i];
                    auto t_rect = threats[cnt].GetRect();
                    threats[cnt].SetRect(t_rect.x, t_rect.y+diff);
                    ++cnt;
                }
            }
            for(int i = cnt; i < n_threats; ++i)
                threats[i].FreeThreat();
            n_threats = cnt;
        };
        ///ScrollBackground();
        ScrollPlatforms();
        ScrollItems();
        ScrollThreats();
        return diff;
    }
    return 0;
}

void Game :: GenObjects()
{
    int c = n_platforms;
    n_platforms = Gen_nplatforms();
    for(int i = c; i < n_platforms; ++i)
        GenPlatform(i);
    c = n_items;
    n_items = Gen_nitems();
    for(int i = c; i < n_items; ++i)
        if (GenItem(i) == false)
        {
            --i;
            --n_items;
        }
    c = n_threats;
    n_threats = Gen_nThreats();
    for(int i = c; i < n_threats; ++i)
        if (GenThreat(i) == false)
        {
            --i;
            --n_threats;
        }
}

OPTION Game :: PlayGame()
{
    Mix_HaltMusic();
    Init();
    bool quit = false;

    int times_per_frame = 1000 / FPS;

    int old_y = character.GetRect().y;

    CharacterMoveType move_type = CharacterMoveType::INVALID;
    while (!quit)
    {
        ///timer.Start();
        bool has_event = SDL_PollEvent(&event) != 0;
        if (has_event)
        {
            if (event.type == SDL_QUIT)
                quit = true;
            move_type = character.GetMoveType();
        }
        auto DoOptions = [&]() -> OPTION
        {
            auto option = GetChosenOption(InGameOptions, has_event);
            switch (option)
            {
                case OPTION::PAUSE_BUTTON:
                    int i = etoi(InGameOptionsPack::GAME_PAUSED);
                    ////in_game_options_pack[etoi(InGameOptionsPack::GAME_PAUSED)].background.Render();
                    while (true)
                    {
                        option = GetChosenOption(OptionsInInGameOptionsPack[i], SDL_PollEvent(&event));
                        if (option != OPTION::NO_OPTION)
                            return option;
                        in_game_options_pack[i].Render();
                        SDL_RenderPresent(renderer);
                    }
                    break;
            }
            return OPTION::NO_OPTION;
        };
        auto DoChar = [&]() -> void
        {
            character.Move();
            character.Cross(move_type);
            character.DoOutOfFrame();
            if (character.current_move_type[uint16_t(CharacterMoveType::JUMP)] == false) /// is falling down
            {
                SDL_Rect cl_rect = character.GetLegsRect();
                for(int i = 0; i < n_platforms; ++i)
                    if (platforms[i].GetRect().y > cl_rect.y && CheckCollision(platforms[i].GetRect(), cl_rect))
                    {
                        PlaySound(character.landing, 1);
                        character.Jump(NormalSpeed);
                        break;
                    }
            }
        };
        auto DoThreats = [&]() -> void
        {
            /// move
            for(int i = 0; i < n_threats; ++i)
            {
                auto& threat = threats[i];
                if (threat.GetRect().y + threat.GetRect().h <= 0)
                    continue;
                switch (threat.GetMotionType())
                {
                    case ThreatMotionType::FLY:
                        {
                            auto rect = threat.GetRect();
                            if (rect.x + rect.w > SCREEN_WIDTH)
                                threat.ChangeDirection(), threat.MoveLeft(); else
                            if (rect.x < 0)
                                threat.ChangeDirection(), threat.MoveRight(); else
                            if (threat.CurrentMoveType() == ThreatMoveType::LEFT)
                                threat.MoveLeft();
                            else
                                threat.MoveRight();
                            break;
                        }

                    case ThreatMotionType::JUMP:
                        threat.Move();

                    case ThreatMotionType::MOVE_ON_PLATFORM:
                        threat.Move();
                        break;

                    case ThreatMotionType::NOT_MOVE:
                        break;
                }
            }
        };
        auto UpdateScore = [&]()
        {
            int current_y = character.GetRect().y;
            if (old_y > current_y)
            {
                d_score += (old_y - current_y)/PIXEL_PER_SCORE;
                old_y = current_y;
            }
        };   
        auto CollectItem = [&]() -> void
        {
            int cnt = 0;
            for(int i = 0; i < n_items; ++i)
                if (character.CollectItem(items[i]))
                {
                    switch (items[i].GetType())
                    {
                        case ItemType::COIN:
                            break;
                        default:
                            items[cnt] = items[i];
                            ++cnt;
                            break;
                    }
                }
                else
                    items[cnt++] = items[i];
            for(int i = cnt; i < n_items; ++i)
                items[i].FreeItem();
            n_items = cnt;
        };
        auto Render = [&]()
        {
            background.Render();
            /**auto tmp = background.GetRect();
            background.SetRect(tmp.x, tmp.y - tmp.h);
            background.Render();
            background.SetRect(tmp.x, tmp.y);*/
            for(int i = 0; i < n_platforms; ++i)
                if (platforms[i].GetRect().y + platforms[i].GetRect().h > 0)
                    platforms[i].Render();
            for(int i = 0; i < n_items; ++i)
                if (items[i].GetRect().y + items[i].GetRect().h > 0)
                    items[i].RenderItem();
            ///cout << n_threats << endl;
            int c = 0;
            for(int i = 0; i < n_threats; ++i)
                if (threats[i].GetRect().y + threats[i].GetRect().h > 0)
                    threats[i].Render();
                    ///debug(ThreatTypeText[etoi(threats[i].GetType())], threats[i].GetRect().y);
            character.Render(); 
            top_frame.Render();
            for(auto o : InGameOptions)
                options[etoi(o)].Render();
            ShowScore();
        }; 
        OPTION o = DoOptions();
        if (o != OPTION::RESUME_BUTTON && o != OPTION::NO_OPTION)
            return o;
        DoChar();
        old_y += ScrollMap();
        DoThreats();
        GenObjects();
        CollectItem();
        UpdateScore();
        Render();
        SDL_RenderPresent(renderer);
        if (character.GetRect().y > SCREEN_HEIGHT)
            return EndGame();
        
        int frame_passed = timer.GetTicks();
        int delay_time = times_per_frame - frame_passed;
        if (delay_time > 0)
            SDL_Delay(delay_time);
    }
    ifstream high_scores_file(MENU_FOLDER + "high_scores.txt");
    for(int x; high_scores_file >> x; high_scores.insert(x));
    high_scores.insert(d_score);
    if (high_scores.size() > NUMBER_OF_HIGH_SCORES)
        high_scores.erase(prev(high_scores.end()));
    high_scores_file.close();
    ofstream g(MENU_FOLDER + "high_scores.txt");
    for(int x : high_scores)
        g << x << ' ';
    g.close();
    return OPTION::EXIT_GAME;
}

void Game :: ResetGame()
{
    d_score = 0;
    n_platforms = 0;
    n_items = 0;
    n_threats = 0;
    in_game_options_pack.clear();
    /**for(int i = 0; i < MAX_PLATFORMS_PER_FRAME; ++i)
        platforms[i].FreePlatform();
    for(int i = 0; i < MAX_ITEMS_PER_FRAME; ++i)
        items[i].FreeItem();*/
}

OPTION Game :: EndGame()
{
    return OPTION::EXIT_GAME;
}

OPTION Game :: ShowMenu()
{
    if (Mix_PlayingMusic() == false)
    {
        LoadSound(menu_sound, SOUND_FOLDER + "menu.mp3");
        PlaySound(menu_sound, INFINITE_LOOP);
    }
    /// make character animation
    character.Init();
    character.SetRect(55, 500);
    ///character.Jump(NormalSpeed);
    platforms[0].LoadPlatform(PlatformType::NORMAL);
    SDL_Rect c_rect = character.GetRect();
    platforms[0].SetRect(c_rect.x, c_rect.y + c_rect.h);
    SDL_Rect p_rect = platforms[0].GetRect();

    menu.Init();
    OPTION res;
    do
    {
        menu.Render();
        res = GetChosenOption(MenuOption, SDL_PollEvent(&event) != 0);        
        platforms[0].Render();
        if (CheckCollision(character.GetLegsRect(), p_rect))
            character.Jump(NormalSpeed);
        character.Move();
        character.Render();
        SDL_RenderPresent(renderer);
    } while (res == OPTION::NO_OPTION);
    return res;
}

void Game :: Start()
{
    InitOptions();
    OPTION current_option = ShowMenu();
    do
    {
        switch (current_option)
        {
            case OPTION::EXIT_GAME:
            case OPTION::EXIT_TEXT:
                return;

            case OPTION::HOME:
                current_option = ShowMenu();
                break;

            case OPTION::HELP:
                current_option = menu.Help();
                break;

            case OPTION::PLAY_BUTTON:
            case OPTION::PLAY_TEXT:
            case OPTION::REPLAY_BUTTON:
                ResetGame();
                current_option = PlayGame();
                break;

            case OPTION::HIGH_SCORES:
                current_option = menu.ShowHighScores();
                break;

            case OPTION::SETTINGS:
                current_option = menu.ShowSettings();
                break;
            
            default:
                current_option = OPTION::EXIT_GAME;
                break;
        }
    } while (true);
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
            CharacterMoveType move_type = CharacterMoveType::INVALID;
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

bool Game :: LoadOption(const OPTION& option)
{
    if (option == OPTION::EXIT)
        return false;
    if (option == OPTION::PLAY)
    {
        PlayGame();
        return false;
    }
    if (option == OPTION::HELP)
    {
        HelpOptions h_option = menu.Help();
        return (h_option == HelpOptions::HOME);
    }
}

void Game :: ShowMenu(const string& font_path, const string& menu_path)
{
    LoadSound(menu_sound, SOUND_FOLDER + "menu.mp3");
    PlaySound(menu_sound, INFINITE_LOOP);
    /**OPTION option = menu.ShowMenu(font_path, menu_path);
    LoadOption(option, font_path, menu_path);*/
    OPTION m_option = menu.ShowMenu(font_path, menu_path);
    bool back_home = LoadOption(m_option);
    while (back_home)
    {
        m_option = menu.ShowMenu();
        back_home = LoadOption(m_option);
    }
}

#endif /// GAME_DEBUG
