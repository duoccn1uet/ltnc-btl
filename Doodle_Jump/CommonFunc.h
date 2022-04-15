#ifndef COMMONFUNC_H_INCLUDED
#define COMMONFUNC_H_INCLUDED

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

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

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
static SDL_Event event;

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
const string BACKGROUND_FOLDER = "img/background/";
const string CHARACTER_FOLDER = "img/character/";
const string PLATFORM_FOLDER = "img/platform/";
const string FONT_FOLDER = "font/";
const string SOUND_FOLDER = "sound/";
const string MENU_FOLDER = "img/menu/";
const string ICON_FOLDER = "img/icon/";
const string ITEM_FOLDER = "img/item/";

/// Character
const float g = 0.4;
const float v0 = 15;
const float pi = acos(-1);
const float delta_alpha = pi/6;
const int d_JumpHeight = v0*v0/(2*g);
const int PRESS_FRAME = 5;
const float push_force = 11;

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
const int OPTION_FONT_SIZE = 30;
const string OPTION_FONT = "KaneiwaAlpRegular-jEpG.ttf";

/// Sound
///const bool SoundOn = true;
const int INFINITE_LOOP = -1;

namespace CommonFunc
{
    // void show() {}
    template <typename T, typename... V> 
    void show(T t, V... v)
    {
     cerr << t; if (sizeof...(v)) cerr << ", "; show(v...);
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

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
static SDL_Event event;

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
