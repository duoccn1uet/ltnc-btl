#ifndef VIEW_H
#define VIEW_H

#include "CommonFunc.h"
#include "Animation.h"

class View
{
public:

    string path;

    // Tọa độ, diện tích của View trên màn hình
    // Đây là tọa độ tương đối so với Viewport
    // Tọa độ tuyệt đối của View trên màn hình = var_render + origin_point.var;
    int x_render      = 0;
    int y_render      = 0;
    int width_render  = 0;
    int height_render = 0;
    int alpha = 255;
    int angle = 0;
    SDL_Point center_point_render = { 0,0 };

    bool texture_may_null = false;
    //Xử lí animation
    vector<Animation*> animation_queue;
    //Các biến backup đưa view về ban đầu sau animation
    int x_render_backup = 0;
    int y_render_backup = 0;
    int width_render_backup = 0;
    int height_render_backup = 0;
    int angle_backup = 0;
    SDL_Point center_point_render_backup = { 0,0 };
    SDL_Texture* backup_texture = 0;
    //View Background
    const View* view_background = 0;
    double x_relative_ratio = 0;
    double y_relative_ratio = 0;
    double width_relative_ratio = 1;
    double height_relative_ratio = 1;

    //Key color RGB
    int R = 0;
    int G = 0;
    int B = 0;

    // Original Width, Height of source image;
    int texture_width = 0;
    int texture_height = 0;

    SDL_Renderer* renderer = 0;

    SDL_Texture* texture = 0;

    // mốc tọa độ để render (Viewport)
    SDL_Point origin_point = {0, 0};

    //xác định diện tích, tọa độ vùng lấy từ image để đưa vào texture
    SDL_Rect* clip = 0;

    SDL_BlendMode blend_mode = SDL_BLENDMODE_NONE;
    View();

    View(SDL_Renderer* gRenderer);
    View(string path, int x = 0, int y = 0);

    ~View();
    int getX();

    int setX(int x);

    int getY();

    int setY(int y);

    int setW(int w);

    int setH(int h);

    int setAlpha(int alpha);

    int setRect(SDL_Rect rect);

    int setCenterPoint(SDL_Point center_point);

    int setKeyColor(SDL_Color key);

    int setRenderer(SDL_Renderer* renderer);

    int setTexture(SDL_Texture* texture);

    SDL_Rect getOriginalTextureSize();

    //Function return false when Texture = 0
    bool loadTexture(string path, bool have_color_key = false);

    int clipImage(int x, int y, int width, int height);

    SDL_BlendMode getBlendMode();

    SDL_BlendMode setBlendMode(SDL_BlendMode blend_mode);

    bool animate();

    void update();

    void setAnimation(string animation, Uint32 duration, Uint32 wait_time = 0, SDL_Point transform_vector = {0, 0});

    void setAnimation(string animation, Uint32 duration, SDL_Texture* temp_texture,Uint32 wait_time = 0);

    void setAnimation(Animation* animation);

    int render(bool render_with_center_point = false);

    void handleMouseEvent(SDL_Event* e);

    void setViewBackground(const View& background);
};

class TextView : public View
{
public:
    TTF_Font* font = 0;
    int font_size;
    TextView();
    TextView(TTF_Font* tFont, int font_size);
    bool makeTextTexture(const char* text, int size, SDL_Color color);
    void render(bool render_with_center_point = false);
};


class Button : public View
{
public:
    std::map<string, SDL_Texture*> button_texture;
    string cur_status = "Mouse Out";
    string pre_status = "Mouse Down";
    Button();
    ~Button();
    void loadTexture(string on_mouse_over, string on_mouse_out);
    void handleMouseEvent(SDL_Event* e);
    void update();
    void render(bool render_with_center_point = false);
    bool beClicked();
};

class Sprite : public View
{
public:
    int frames_number = 0;
    int sheet_rows = 0;
    int sheet_cols = 0;
    int curr_frame = 0;
    SDL_Rect frame_rect = { 0,0,0,0 };
    int fps = 60;
    Uint32 pre_frame_time = 0;
    Sprite(int frames_number, int sheet_rows, int sheet_cols, SDL_Rect frame_rect, int fps = 60);
    void render();
};

#endif /// VIEW_H