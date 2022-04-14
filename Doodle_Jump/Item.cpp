#include "Item.h"

Item :: Item()
{

}

Item :: ~Item()
{

}

void Item :: LoadSound(const string& path)
{
    CommonFunc::LoadSound(collect_sound, path);
}

void Item :: LoadItem(const string& path, SDL_Renderer*& renderer)
{
    ///img.LoadImg(path, renderer);
}

/**void Item :: AddItem(const int& x, const int& y)
{
    position.eb(x, y);
}

void Item :: DeleteItem(const int& y)
{

}*/