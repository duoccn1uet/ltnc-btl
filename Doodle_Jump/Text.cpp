#include "Text.h"

Text :: Text()
{
    d_text_color = WHITE_RGBA;
}

Text :: ~Text()
{
    ///delete d_font;
}

void Text :: SetColor(d_Text_Color color)
{
    if (color == d_Text_Color::RED_TEXT)
        d_text_color = RED_RGBA; else
    if (color == d_Text_Color::BLACK_TEXT)
        d_text_color = BLACK_RGBA; else
    if (color == d_Text_Color::WHITE_TEXT)
        d_text_color = WHITE_RGBA;
}

void Text :: CreateText()
{
    Free();
    SDL_Surface* text_surface = TTF_RenderText_Blended(d_font, d_text_content.c_str(), d_text_color);
    ///SDL_Surface* text_surface = TTF_RenderText_Blended(d_font, d_text_content.c_str(), d_text_color);
    if (text_surface == nullptr)
        cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << '\n';
    else
    {
        d_object = SDL_CreateTextureFromSurface(renderer, text_surface);
        if (d_object == nullptr)
            cout << "Unable to create texture from rendered text! SDL Error: " << TTF_GetError() << '\n';
        else
        {
            d_rect.w = text_surface->w;
            d_rect.h = text_surface->h;
        }
        SDL_FreeSurface(text_surface);
    }
}

void Text :: SetFont(const string& path, int font_size)
{
    d_font = TTF_OpenFont(path.c_str(), font_size);
    if (d_font == nullptr)
        cout << "Failed to load font from " << path << "! SDL_ttf Error: " << TTF_GetError() << '\n';
}

void Text :: SetFontSType(int type)
{
    TTF_SetFontStyle(d_font, type);
}

void Text :: RenderText()
{
    Render(nullptr);
}
