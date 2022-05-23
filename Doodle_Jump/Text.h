#ifndef TEXT_H
#define TEXT_H

#include "CommonFunc.h"
#include "ImgProcess.h"

enum class d_Text_Color : short
{
    RED_TEXT = 0,
    WHITE_TEXT,
    BLACK_TEXT
};

class Text: public ImgProcess
{
public:

    Text();
    ~Text();

    void SetContent(const string& text_content);
    void SetColor(d_Text_Color color);
    void SetFont(const string& path, int font_size);
    void SetFontSType(int type);
    void CreateText();
    void CreateText(const string& FONT_NAME, const int& font_size, const string& text_content, 
                    d_Text_Color color = d_Text_Color::WHITE_TEXT, int style = TTF_STYLE_NORMAL);
    void Render();

private:

    string d_text_content;
    SDL_Color d_text_color;
    TTF_Font *d_font;
};

#endif // TEXT_H
