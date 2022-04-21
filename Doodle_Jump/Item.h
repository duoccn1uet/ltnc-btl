#ifndef ITEM_H
#define ITEM_H

#include "CommonFunc.h"
#include "ImgProcess.h"
#include "Motion.h"

enum class ItemType
{
    COIN, ROCKET, SPRINGS, nItemType, INVALID
};

enum class ItemStatus
{
    SHOW, APPLY, LEAVE, nItemStatus
};

const string ItemTypeText[] = {"coin", "rocket", "springs"};
const string ItemStatusText[] = {"show", "apply", "leave"};
/// [type][status]
const vector <vector<int>> ItemFrame = {{1, 0, 0},
                                        {1, 1, 0},
                                        {1, 1, 0}};

class Item
{
public:

    Item();
    ~Item();

    ItemType GetType() const {return static_cast <ItemType> (type);}
    ItemStatus GetStatus() const {return static_cast <ItemStatus> (status);}
    const SDL_Rect GetRect();
    void SetRect(const int& x, const int& y);
    void SetItem(const ItemType& _type, const ItemStatus& _status);
    void RenderItem();
    void RenderSound();

private:

    Mix_Chunk* apply_sound = nullptr;
    vector <ImgProcess> img;
    uint16_t type;
    uint16_t status;
    int frame_ptr = 0;
};

#endif ///ITEM_H