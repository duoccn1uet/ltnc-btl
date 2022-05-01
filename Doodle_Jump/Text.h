#ifndef TEXT_H
#define TEXT_H

#include "CommonFunc.h"
#include "ImgProcess.h"

enum class d_Text_Color : int
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

    void SetContent(const string& text_content) {d_text_content = text_content;}
    void SetColor(d_Text_Color color);
    void SetFont(const string& path, int font_size);
    void SetFontSType(int type);
    void CreateText();
    void RenderText();

private:

    string d_text_content;
    SDL_Color d_text_color;
    TTF_Font *d_font;
};

#endif // TEXT_H
