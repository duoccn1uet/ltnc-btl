#include "View.h"

View::View()
{
    //do nothing
};

View::View(SDL_Renderer* gRenderer)
{
    this->renderer = gRenderer;
}

View::View(string path, int x, int y)
{

    this->x_render = x;
    this->y_render = y;
    this->path = path;

};

View::~View()
{
}

int View::getX()
{

    return this->x_render;

};

int View::getY()
{

    return this->y_render;

};

int View::setY(int y)
{

    this->y_render = y;
    return 1;

};

int View::setX(int x)
{

    this->x_render = x;
    return 1;

};

int View::setW(int w)
{

    this->width_render = w;
    return 1;

};

int View::setH(int h)
{

    this->height_render = h;
    return 1;

}

int View::setAlpha(int alpha)
{
    if (this->getBlendMode() != SDL_BLENDMODE_BLEND)
    {
        this->setBlendMode(SDL_BLENDMODE_BLEND);
    }
    else
    {
        SDL_SetTextureAlphaMod(this->texture, alpha);
        this->alpha = alpha;
    }
    return 1;
}

int View::setRect(SDL_Rect rect)
{
    this->x_render		= rect.x;
    this->y_render		= rect.y;
    this->width_render  = rect.w;
    this->height_render = rect.h;
    return 1;
}

int View::setCenterPoint(SDL_Point center_point)
{
    this->center_point_render.x = center_point.x;
    this->center_point_render.y = center_point.y;
    this->x_render = center_point.x - this->width_render/2;
    this->y_render = center_point.y - this->height_render/2;
    return 0;
}

int View::setKeyColor(SDL_Color key)
{
    this->R = key.r;
    this->G = key.g;
    this->B = key.b;
    return 0;
}

int View::setRenderer(SDL_Renderer* renderer)
{

    this->renderer = renderer;
    return 1;

}
int View::setTexture(SDL_Texture* texture)
{
    this->texture = texture;
    this->animation_queue.clear();
    return 0;
}
SDL_Rect View::getOriginalTextureSize()
{
    if (this->texture_width == 0 || this->texture_height == 0)
    {
        SDL_QueryTexture(this->texture, 0, 0, &this->texture_width, &this->texture_height);
    }
    return SDL_Rect { 0, 0, texture_width, texture_height };
}
;

int View::clipImage(int x, int y,int width, int height)
{
    this->clip = new SDL_Rect;
    this->clip->x = x;
    this->clip->y = y;
    this->clip->w = width;
    this->clip->h = height;
    return 1;

}

SDL_BlendMode View::getBlendMode()
{
    SDL_GetTextureBlendMode(this->texture, &this->blend_mode);
    return this->blend_mode;
}

SDL_BlendMode View::setBlendMode(SDL_BlendMode blend_mode)
{
    SDL_SetTextureBlendMode(this->texture,blend_mode);
    this->blend_mode = blend_mode;
    return this->blend_mode;
}

bool View::animate()
{
    bool all_done = true;
    for (int i = 0; i < animation_queue.size(); i++)
    {
        if (animation_queue[i]->ended) continue;
        if (animation_queue[i]->temp_time == 0)
        {
            animation_queue[i]->temp_time = SDL_GetTicks();
        };
        if (SDL_GetTicks() - animation_queue[i]->temp_time < animation_queue[i]->wait_time)
        {
            continue;
        }
        if (animation_queue[i]->name.find("Scale Up") != string::npos)
        {
            double ratio_scale = 2;
            SDL_Point center_point;
            if (animation_queue[i]->start_time == 0)
            {
                animation_queue[i]->start_time = SDL_GetTicks();
                animation_queue[i]->ended = false;
            }
            center_point = this->center_point_render_backup;
            Uint32 time_offset = SDL_GetTicks() - animation_queue[i]->start_time;
            if (time_offset > animation_queue[i]->duration)
            {
                animation_queue[i]->ended = true;
                continue;
            }
            //ratio_scale = ratio_scale - double(time_offset) / double(animation_queue[i]->duration) * ratio_scale + 1;
            if (time_offset < animation_queue[i]->duration/2)
                ratio_scale = (ratio_scale - 1) * double(time_offset) / double(animation_queue[i]->duration / 2) + 1;
            else ratio_scale = (1 - ratio_scale) * (double(time_offset) / double(animation_queue[i]->duration / 2) - 1) + ratio_scale;
            this->width_render = double(this->width_render_backup) * ratio_scale;
            this->height_render = double(this->height_render_backup) * ratio_scale;
            this->x_render = center_point.x - this->width_render / 2;
            this->y_render = center_point.y - this->height_render / 2;
        };

        if (animation_queue[i]->name.find("Appear") != string::npos)
        {
            double ratio_scale = 1;
            SDL_Point center_point;
            if (animation_queue[i]->start_time == 0)
            {
                animation_queue[i]->start_time = SDL_GetTicks();
                animation_queue[i]->ended = false;
            }
            center_point = this->center_point_render_backup;
            Uint32 time_offset = SDL_GetTicks() - animation_queue[i]->start_time;
            if (time_offset > animation_queue[i]->duration)
            {
                animation_queue[i]->ended = true;
                continue;
            };
            ratio_scale = double(time_offset) / double(animation_queue[i]->duration) * ratio_scale;
            this->width_render = double(this->width_render_backup) * ratio_scale;
            this->height_render = double(this->height_render_backup) * ratio_scale;
            this->x_render = center_point.x - this->width_render / 2;
            this->y_render = center_point.y - this->height_render / 2;
        };

        if (animation_queue[i]->name.find("Disappear") != string::npos)
        {
            double ratio_scale = 1;
            SDL_Point center_point;
            if (animation_queue[i]->start_time == 0)
            {
                animation_queue[i]->start_time = SDL_GetTicks();
                animation_queue[i]->ended = false;
            }
            center_point = this->center_point_render_backup;
            Uint32 time_offset = SDL_GetTicks() - animation_queue[i]->start_time;
            if (time_offset > animation_queue[i]->duration)
            {
                animation_queue[i]->ended = true;
                continue;
            };
            ratio_scale = ratio_scale - double(time_offset) / double(animation_queue[i]->duration);
            this->width_render = double(this->width_render_backup) * ratio_scale;
            this->height_render = double(this->height_render_backup) * ratio_scale;
            this->x_render = center_point.x - this->width_render / 2;
            this->y_render = center_point.y - this->height_render / 2;

        };
        if (animation_queue[i]->name.find("Transform") != string::npos)
        {
            if (animation_queue[i]->start_time == 0)
            {
                animation_queue[i]->start_time = SDL_GetTicks();
                animation_queue[i]->ended = false;
            }
            if (animation_queue[i]->transform_vector.x != 0 || animation_queue[i]->transform_vector.y != 0)
            {
                Uint32 time_offset = SDL_GetTicks() - animation_queue[i]->start_time;
                double ratio_time = (double)time_offset / (double)animation_queue[i]->duration;
                if (time_offset > animation_queue[i]->duration)
                {
                    animation_queue[i]->ended = true;
                    continue;
                };
                if (this->center_point_render_backup.x != 0 && this->center_point_render_backup.y != 0)
                {
                    SDL_Point new_center_point;
                    new_center_point.x = this->center_point_render_backup.x + (double)animation_queue[i]->transform_vector.x * ratio_time;
                    new_center_point.y = this->center_point_render_backup.y + (double)animation_queue[i]->transform_vector.y * ratio_time;
                    this->setCenterPoint(new_center_point);
                }
                else
                {
                    this->x_render = this->x_render_backup + animation_queue[i]->transform_vector.x * ratio_time;
                    this->y_render = this->y_render_backup + animation_queue[i]->transform_vector.y * ratio_time;
                }
            }
            else cout << "FAILED TO DO TRANSFORM ANIMATION" << endl;
        }
        if (animation_queue[i]->name.find("Fade In") != string::npos)
        {
            double ratio = 1;
            int alpha;
            if (animation_queue[i]->start_time == 0)
            {
                animation_queue[i]->start_time = SDL_GetTicks();
                animation_queue[i]->ended = false;
            };
            if (this->getBlendMode() != SDL_BLENDMODE_BLEND)
            {
                this->setBlendMode(SDL_BLENDMODE_BLEND);
            };
            Uint32 time_offset = SDL_GetTicks() - animation_queue[i]->start_time;
            if (time_offset > animation_queue[i]->duration)
            {
                animation_queue[i]->ended = true;
                continue;
            };
            ratio = (double)time_offset / (double)animation_queue[i]->duration;
            alpha = ratio * 255;
            this->setAlpha(alpha);
        };
        if (animation_queue[i]->name.find("Fade Out") != string::npos)
        {
            double ratio = 1;
            int alpha;
            if (animation_queue[i]->start_time == 0)
            {
                animation_queue[i]->start_time = SDL_GetTicks();
                animation_queue[i]->ended = false;
            };
            if (this->getBlendMode() != SDL_BLENDMODE_BLEND)
            {
                this->setBlendMode(SDL_BLENDMODE_BLEND);
            };
            Uint32 time_offset = SDL_GetTicks() - animation_queue[i]->start_time;
            if (time_offset > animation_queue[i]->duration)
            {
                animation_queue[i]->ended = true;
                continue;
            };
            ratio = (double)time_offset / (double)animation_queue[i]->duration;
            alpha = (1-ratio) * 255;
            this->setAlpha(alpha);
        };
        if (animation_queue[i]->name.find("Switch Texture") != string::npos)
        {
            if (animation_queue[i]->start_time == 0)
            {
                animation_queue[i]->start_time = SDL_GetTicks();
                animation_queue[i]->ended = false;
                this->texture = animation_queue[i]->temp_texture;
            }
            Uint32 time_offset = SDL_GetTicks() - animation_queue[i]->start_time;
            this->texture = animation_queue[i]->temp_texture;
            if (time_offset > animation_queue[i]->duration)
            {
                animation_queue[i]->ended = true;
                this->texture = this->backup_texture;
                continue;
            };

        };
        if (animation_queue[i]->name.find("Rotate") != string::npos)
        {
            if (animation_queue[i]->start_time == 0)
            {
                animation_queue[i]->start_time = SDL_GetTicks();
                animation_queue[i]->ended = false;
                this->angle_backup = this->angle;
            };
            Uint32 time_offset = SDL_GetTicks() - animation_queue[i]->start_time;
            if (time_offset > animation_queue[i]->duration)
            {
                animation_queue[i]->ended = true;
                continue;
            };
            this->angle = angle_backup + animation_queue[i]->angle_rotate * (double)time_offset / (double)animation_queue[i]->duration;
        };
        if (animation_queue[i]->name.find("Cut Down") != string::npos)
        {
            if (animation_queue[i]->start_time == 0)
            {
                animation_queue[i]->start_time = SDL_GetTicks();
                animation_queue[i]->ended = false;
            }
            Uint32 time_offset = SDL_GetTicks() - animation_queue[i]->start_time;
            if (time_offset > animation_queue[i]->duration)
            {
                animation_queue[i]->ended = true;
                continue;
            };
            SDL_Rect origional_size = this->getOriginalTextureSize();
            int new_y_render = this->y_render_backup + this->height_render_backup * (double)time_offset / (double)animation_queue[i]->duration;
            int new_height_render = this->height_render_backup - (new_y_render - this->y_render_backup);
            int new_clip_height = double(new_height_render) / double(this->height_render_backup) * origional_size.h;
            //this->y_render = this->y_render_backup + this->height_render_backup * (double)time_offset / (double)animation_queue[i]->duration;
            this->clipImage(0, 0, origional_size.w, new_clip_height);
            this->setRect({ this->x_render_backup, new_y_render, this->width_render_backup, new_height_render });
        };
    };
    for (auto it = animation_queue.begin(); it < animation_queue.end(); it++)
    {
        if (!(*it)->ended)
        {
            all_done = false;
            break;
        }
    };
    return all_done;
}
void View::update()
{
    if (this->view_background != 0)
    {
        this->origin_point.x = view_background->origin_point.x + view_background->x_render;
        this->origin_point.y = view_background->origin_point.y + view_background->y_render;
        this->x_render = this->view_background->width_render * this->x_relative_ratio;
        this->y_render = this->view_background->height_render * this->y_relative_ratio;
        this->width_render = this->view_background->width_render * this->width_relative_ratio;
        this->height_render = this->view_background->height_render * this->height_relative_ratio;
    };

    if (View::animate())
    {
        this->animation_queue.clear();
        this->x_render_backup = 0;
        this->y_render_backup = 0;
        this->width_render_backup = 0;
        this->height_render_backup = 0;
        this->angle_backup = 0;
        this->center_point_render_backup = { 0,0 };
    };
}
;

void View::setAnimation(string animation, Uint32 duration, Uint32 wait_time, SDL_Point transform_vector)
{
    this->x_render_backup = this->x_render;
    this->y_render_backup = this->y_render;
    this->width_render_backup = this->width_render;
    this->height_render_backup = this->height_render;
    this->center_point_render_backup = { this->x_render + this->width_render / 2, this->y_render + this->height_render / 2 };
    Animation* new_animation = new Animation(animation, duration, transform_vector, wait_time);
    this->animation_queue.push_back(new_animation);
    if (animation.find("Fade In") != string::npos)
    {
        this->setAlpha(0);
    };
}

void View::setAnimation(string animation, Uint32 duration, SDL_Texture* temp_texture, Uint32 wait_time)
{
    Animation* new_animation = new Animation(animation, duration, temp_texture, wait_time);
    this->animation_queue.push_back(new_animation);
    this->backup_texture = this->texture;
    this->texture = temp_texture;
}

void View::setAnimation(Animation* animation)
{
    this->animation_queue.push_back(animation);
}

int View::render(bool render_with_center_point)
{
    if (this->texture == 0 && !this->texture_may_null) cerr << "Please load texture for View" << endl;
    if (this->renderer == 0) cerr << "Please load renderer for View" << endl;
    View::update();
    if ((this->center_point_render.x != 0 || this->center_point_render.y != 0) && render_with_center_point)
    {
        this->x_render = this->center_point_render.x - this->width_render / 2;
        this->y_render = this->center_point_render.y - this->height_render / 2;
    }
    this->angle = this->angle % 360;
    SDL_Rect rect_des = { this->x_render + origin_point.x, this->y_render + origin_point.y, this->width_render, this->height_render };
    if (this->angle == 0)
        SDL_RenderCopy(this->renderer, texture, this->clip, &rect_des);
    else
    {
        if (angle < 0) this->angle = -angle;
        SDL_RenderCopyEx(this->renderer, this->texture, this->clip, &rect_des, this->angle, 0, SDL_FLIP_NONE);
    }
    if (alpha != 255)
    {
        this->setAlpha(255);
    }
    return 1;

}

void View::setViewBackground(const View& background)
{
    if (background.renderer == 0)
        cerr << "Invalid Background" << endl;
    else
    {

        this->origin_point.x = background.origin_point.x + background.x_render;
        this->origin_point.y = background.origin_point.y + background.y_render;
        this->x_relative_ratio = double(this->x_render) / double(background.width_render);
        this->y_relative_ratio = double(this->y_render) / double(background.height_render);
        this->width_relative_ratio = double(this->width_render) / double(background.width_render);
        this->height_relative_ratio = double(this->height_render) / double(background.height_render);
        this->view_background = &background;
    }
}

//Function return false when Texture = 0
bool View::loadTexture(string path, bool have_color_key)
{

    SDL_Surface* temp = IMG_Load(path.c_str());

    if (temp == 0)
        cout << "Unable to load image (path: " << path << " )" << endl << "Error :" << SDL_GetError() << endl;
    else
    {

        if (have_color_key)
            SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB(temp->format, this->R, this->G, this->B));

        SDL_Texture* nTexture = SDL_CreateTextureFromSurface(this->renderer, temp);
        this->texture = nTexture;
        SDL_FreeSurface(temp);

    };

    if (this->texture != 0 && this->width_render == 0 && this->height_render == 0)
    {

        SDL_QueryTexture(this->texture, 0, 0, &(this->width_render), &(this->height_render));
        SDL_QueryTexture(this->texture, 0, 0, &(this->texture_width), &(this->texture_height));
        //this->center_point_render = { this->width_render / 2, this->height_render / 2 };
        return true;

    }
    else
        return false;

};

TextView::TextView()
{
}

TextView::TextView(TTF_Font* tFont, int font_size)
{
    this->font_size = font_size;
    this->font = tFont;
}

bool TextView::makeTextTexture(const char* text, int size, SDL_Color color)
{
    if (this->texture != 0)
    {
        SDL_DestroyTexture(this->texture);
        this->animation_queue.clear();
        this->texture = 0;
    }
    SDL_Surface* temp_surface = TTF_RenderText_Blended(this->font, text, color);
    if (temp_surface == 0)
    {
        cerr << "Unable to make Text Surface, TTF_Error : " << TTF_GetError();
        return false;
    }
    else
    {
        double ratio = double(size) / double(this->font_size);
        this->width_render = double(temp_surface->w) * ratio;
        this->height_render = double(temp_surface->h) * ratio;
        if (this->center_point_render.x != 0 && this->center_point_render.y != 0)
        {
            this->x_render = this->center_point_render.x - this->width_render / 2;
            this->y_render = this->center_point_render.y - this->height_render / 2;
        }
        //this->center_point_render = {this->origin_point.x + this->width_render / 2,this->origin_point.y + this->height_render / 2 };
        if (this->texture != 0)
        {
            cout << "TextView texture pointer isn't 0 to make Texture" << endl;
            return false;
        };
        this->texture = SDL_CreateTextureFromSurface(this->renderer, temp_surface);
        if (this->texture == 0)
        {
            cout << "Create Texture from surface error : " << SDL_GetError() << endl;
            return false;
        };
        SDL_FreeSurface(temp_surface);
    }
    return true;
}

void TextView::render(bool render_with_center_point)
{
    /*if ((this->center_point_render.x != 0 || this->center_point_render.y != 0) && render_with_center_point) {
    	this->x_render = this->center_point_render.x - this->width_render/2;
    	this->y_render = this->center_point_render.y - this->height_render/2;
    }*/
    View::render();
}

Button::Button()
{
}

Button::~Button()
{
    if (button_texture["Mouse Over"] != 0) SDL_DestroyTexture(button_texture["Mouse Over"]);
    if (button_texture["Mouse Down"] != 0) SDL_DestroyTexture(button_texture["Mouse Down"]);
    if (button_texture["Mouse Up"] != 0) SDL_DestroyTexture(button_texture["Mouse Up"]);
    if (button_texture["Mouse Out"] != 0) SDL_DestroyTexture(button_texture["Mouse Out"]);
}

void Button::loadTexture(string on_mouse_over, string on_mouse_out)
{

    View::loadTexture(on_mouse_over);
    this->button_texture["Mouse Over"] = this->texture;
    this->button_texture["Mouse Down"] = this->texture;
    this->button_texture["Mouse Up"] = this->texture;


    View::loadTexture(on_mouse_out);
    this->button_texture["Mouse Out"] = this->texture;

}
void Button::handleMouseEvent(SDL_Event* e)
{
    bool inside = true;
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEBUTTONDOWN)
    {
        SDL_Point MOUSE_POSITION;
        SDL_GetMouseState(&MOUSE_POSITION.x, &MOUSE_POSITION.y);
        //cout << MOUSE_POSITION.x << "  -  " << MOUSE_POSITION.y << endl;
        if (MOUSE_POSITION.x < this->origin_point.x + this->x_render)
        {
            inside = false;
        }
        //Mouse is right of the button
        else if (MOUSE_POSITION.x > this->origin_point.x + this->x_render + this->width_render)
        {
            inside = false;
        }
        //Mouse above the button
        else if (MOUSE_POSITION.y  < this->origin_point.y + this->y_render)
        {
            inside = false;
        }
        //Mouse below the button
        else if (MOUSE_POSITION.y > this->origin_point.y + this->y_render + this->height_render)
        {
            inside = false;
        }

    }
    if (!inside)
        this->cur_status = "Mouse Out";
    else
    {
        switch (e->type)
        {
        case SDL_MOUSEMOTION:
            this->cur_status = "Mouse Over";
            break;

        case SDL_MOUSEBUTTONDOWN:
            this->cur_status = "Mouse Down";
            break;

        case SDL_MOUSEBUTTONUP:
            this->cur_status = "Mouse Up";
            break;
        }
    }
}
void Button::update()
{
    //if (pre_status != cur_status) {
    pre_status = cur_status;
    this->texture = button_texture[cur_status];
    //};
}
void Button::render(bool render_with_center_point)
{
    Button::update();
    if ((this->center_point_render.x != 0 || this->center_point_render.y != 0) && render_with_center_point)
    {
        this->x_render = this->center_point_render.x - this->width_render / 2;
        this->y_render = this->center_point_render.y - this->height_render / 2;
    }
    View::render();
}
bool Button::beClicked()
{
    return this->cur_status == "Mouse Up" && (this->pre_status == "Mouse Down" || this->pre_status == "Mouse Over");
}
;

Sprite::Sprite(int frames_number, int sheet_rows, int sheet_cols, SDL_Rect frame_rect, int fps)
{
    this->frames_number = frames_number;
    this->sheet_cols = sheet_cols;
    this->sheet_rows = sheet_rows;
    this->frame_rect = frame_rect;
    this->fps = fps;
}

void Sprite::render()
{
    if (this->pre_frame_time == 0)
    {
        this->pre_frame_time = SDL_GetTicks();
        this->clipImage(this->frame_rect.x, this->frame_rect.y, this->frame_rect.w, this->frame_rect.h);
    }
    else
    {
        Uint32 curr_time = SDL_GetTicks();
        if (curr_time - this->pre_frame_time >= 1000 / 40)
        {

            this->pre_frame_time = curr_time;
            this->curr_frame = (this->curr_frame + 1) % this->frames_number;

        }

        int curr_frame_row = this->curr_frame / this->sheet_cols;
        int curr_frame_col = this->curr_frame % this->sheet_cols;
        this->clipImage(this->frame_rect.x + this->frame_rect.w * curr_frame_col,
                        this->frame_rect.y + this->frame_rect.h * curr_frame_row,
                        this->frame_rect.w,  this->frame_rect.h);
    }
    View::render();
}
