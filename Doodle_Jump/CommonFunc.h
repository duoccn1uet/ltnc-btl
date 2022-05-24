#ifndef COMMONFUNC_H_INCLUDED
#define COMMONFUNC_H_INCLUDED

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#define foru(i, a, b) for(int i = a, _b = (b)+1; i < _b; ++i)
#define ford(i, a, b) for(int i = a, _b = (b)-1; i > _b; --i)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define fr freopen
#define eb emplace_back
#define ep emplace

using namespace std;

///#define COMMONFUNC_DEBUG
#ifndef COMMONFUNC_DEBUG

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Event event;
extern string MAP_NAME;
extern mt19937 rd;

/// Screen
const string WINDOW_TITLE = "WELCOME TO MY EMPIRE";

const int SCREEN_WIDTH = 542;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int RENDER_DRAW_COLOR = 0xff;

/// Delay
const int SHORT_DELAY = 60;
const int FPS = 70;

/// Folder
extern string BACKGROUND_FOLDER;
extern string CHARACTER_FOLDER;
extern string PLATFORM_FOLDER;
extern string FONT_FOLDER;
extern string SOUND_FOLDER;
extern string MENU_FOLDER;
extern string OPTION_FOLDER;
extern string ITEM_FOLDER;

/// Character
const float g = 0.4;
const float v0 = 15;
const float pi = acos(-1);
const float delta_alpha = pi/6;
const int d_JumpHeight = v0*v0/(2*g);
const int PRESS_FRAME = 5;
const float push_force = 10;

/// Platforms
const int d_min_dist = 60;

/// Random
const int MAX_RANDOM_TIMES = 15;

/// Color
#define RED_RGBA {255, 0, 0, 255}
#define WHITE_RGBA {255, 255, 255, 255}
#define BLACK_RGBA {0, 0, 0, 255}

/// Score
const int SCORE_FONT_SIZE = 35;
const string SCORE_FONT = "DoodleJump.ttf";

/// Menu
const int OPTION_FONT_SIZE = 40;
const string OPTION_FONT = "DoodleJump.ttf";
///const string OPTION_FONT = "DoodleJump.ttf";

/// Sound
///const bool SoundOn = true;
const int INFINITE_LOOP = -1;/// {} // end recursion

/// Option

enum class OPTION: short
{
    HOME, 
    PLAY_TEXT, HELP, EXIT_TEXT, HIGH_SCORES, SETTINGS,
    ON_TEXT, OFF_TEXT, EASY_TEXT, MEDIUM_TEXT, HARD_TEXT, RESET_HIGH_SCORES,
    PAUSE_BUTTON, RESUME_BUTTON, PLAY_BUTTON, REPLAY_BUTTON,
    nOPTION, EXIT_GAME, NO_OPTION
};

const string OptionText[] = {"home", 
                             "play_text", "help", "exit_text", "high_scores", "settings",
                             "on_text", "off_text", "easy_text", "medium_text", "hard_text", "reset_high_scores",
                             "pause_button", "resume_button", "play_button", "replay_button"};

/// other
const int DECIMAL_DIGITS_X10 = 1e3;

namespace CommonFunc
{
    //template <typename... ArgTypes>
    ////void show(ArgTypes... g);
    void show();
    template <typename T, typename... V> void show(T t, V... v)
    {
        cerr << t; if (sizeof...(v)) {cerr << ", "; show(v...);}
    }
    #define debug(...) cerr << '[' << #__VA_ARGS__ << "]   =   [", show(__VA_ARGS__), cerr << "]\n"

    template <class X>
    bool mini(X& a, const X& b)
    {
        if (a > b) {a = b; return true;} return false;
    }

    template <class X>
    bool maxi(X& a, const X& b)
    {
        if (a < b) {a = b; return true;} return false;
    }

    long long rand(long long Left, long long Right);
    bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);
    int SqrDist(const SDL_Rect& a, const SDL_Rect& b);
    bool LoadSound(Mix_Music*& sound, const string& path);
    bool LoadSound(Mix_Chunk*& sound, const string& path);
    void PlaySound(Mix_Music*& sound, int loop);
    void PlaySound(Mix_Chunk*& sound, int loop);
    void SetMapName(const string& _MAP_NAME);
    template <class E> int etoi(const E& x) {return int(x);}
}

using namespace CommonFunc;

#else

namespace CommonFunc
{
    void show();
    template <typename T, typename... V> void show(T t, V... v);
    #define debug(...) cerr << '[' << #__VA_ARGS__ << "]   =   [", show(__VA_ARGS__), cerr << "]\n"

    template <class X>
    bool mini(X& a, const X& b)
    {
        if (a > b) {a = b; return true;} return false;
    }

    template <class X>
    bool maxi(X& a, const X& b)
    {
        if (a < b) {a = b; return true;} return false;
    }

    long long rand(long long Left, long long Right);
    bool CheckCollision(const SDL_Rect& a, const SDL_Rect& b);
    int SqrDist(const SDL_Rect& a, const SDL_Rect& b);
}

using namespace CommonFunc;

extern SDL_Window* window = nullptr;
extern SDL_Renderer* renderer = nullptr;
extern SDL_Event event;

/// Screen
const string WINDOW_TITLE = "WELCOME TO MY EMPIRE";

const int SCREEN_WIDTH = 542;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int RENDER_DRAW_COLOR = 0xff;

/// Delay
const int SHORT_DELAY = 60;
const int FPS = 70;

/// Folder
const string BACKGROUND_FOLDER = "img\\background\\";
const string CHARACTER_FOLDER = "img\\character\\";
const string PLATFORM_FOLDER = "img\\platform\\";
const string FONT_FOLDER = "font\\";

/// Character
const float g = 0.3;
const float v0 = 12;
const float pi = acos(-1);
const float cosa = cos(pi/9);
const int d_JumpHeight = v0*v0/(2*g);

/// Platforms
const int d_min_dist = 60;

/// Random
const int MAX_RANDOM_TIMES = 15;

/// Color
#define RED_RGBA {255, 0, 0, 255}
#define WHITE_RGBA {255, 255, 255, 255}
#define BLACK_RGBA {0, 0, 0, 255}

/// Score
const int SCORE_FONT_SIZE = 25;
const string SCORE_FONT = "Minecraft Evenings.ttf";

/// Menu
const string OPTION_FONT = SCORE_FONT;

#endif // COMMONFUNC_H_DEBUG

#endif // COMMONFUNC_H_INCLUDED
