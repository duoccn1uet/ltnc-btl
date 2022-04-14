#ifndef ITEM_H
#define ITEM_H

#include "CommonFunc.h"
#include "ImgProcess.h"
#include "Motion.h"

enum class ItemType
{
    COIN, ROCKET, SPRINGS, nItemType
};

const string ItemText[] = {"coin", "rocket", "springs"};

class Item: public ImgProcess
{
public:

    Item();
    ~Item();

    void SetItemType(const ItemType& _type) {type = _type;}
    void LoadSound(const string& path);
    void LoadItem(const string& path, SDL_Renderer*& renderer);

private:

    Mix_Chunk* collect_sound = nullptr;
    ItemType type;
};

#endif ///ITEM_H