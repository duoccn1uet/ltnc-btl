#include "Item.h"

///#define ITEM_DEBUG
#ifndef ITEM_DEBUG

Item :: Item()
{
    type = uint16_t(ItemType :: nItemType);
    status = uint16_t(ItemStatus::nItemStatus);
}

Item :: ~Item()
{
    FreeItem();
}

const SDL_Rect Item :: GetRect()
{
    if (img.empty())
        cout << "Items has no frame or not been initialized\n";
    else
        return img[cur_frame].GetRect();
}

void Item :: SetRect(const int& x, const int& y)
{
    if (img.empty())
        cout << "Items has no frame or not been initialized\n";
    else
        img[cur_frame].SetRect(x, y);
}

/// [type][status]

void Item :: SetItem(const ItemType& _type, const ItemStatus& _status)
{
    if (type != uint16_t(_type) || status != uint16_t(_status))
    {
        type = uint16_t(_type);
        status = uint16_t(_status);
        img.resize(ItemFrame[type][status]);
        for(int i = 0; i < img.size(); ++i)
            img[i].LoadImg(ITEM_FOLDER + ItemTypeText[type] + '_' + ItemStatusText[status] + '_' + to_string(i) + ".png");
        cur_frame = 0;
        if (_status == ItemStatus::APPLY)
            LoadSound(apply_sound, SOUND_FOLDER + ItemTypeText[type] + "_apply.wav");
    }
    ///for(int i = 0; i < img.size(); ++i)
    ///    img[i].LoadImg(ITEM_FOLDER + ItemTypeText[type] + '_' + ItemStatusText[status] + '_' + to_string(i) + ".png");
}

void Item :: RenderItem()
{
    if (img.empty())
        return;
    ///cout << cur_frame << endl;
    ///img[cur_frame].LoadImg(ITEM_FOLDER + "coin_show_0.png");
    img[cur_frame].LoadImg(ITEM_FOLDER + ItemTypeText[type] + '_' + ItemStatusText[status] + '_' + to_string(cur_frame) + ".png");
    img[cur_frame].Render();
    if (++cur_frame == img.size())
        cur_frame = 0;
}

void Item :: RenderSound()
{
    switch (static_cast <ItemStatus>(status))
    {
        case ItemStatus::APPLY:
            PlaySound(apply_sound, 1);
            break;
        default:
            break;
    }
}


void Item :: FreeItem()
{
    Mix_FreeChunk(apply_sound);
    apply_sound = nullptr;
    for(auto& x : img)
        x.Free();
    img.clear();
    type = uint16_t(ItemType :: nItemType);
    status = uint16_t(ItemStatus::nItemStatus);
    cur_frame = 0;
}

#else

Item :: Item()
{
    type = uint16_t(ItemType :: nItemType);
    status = uint16_t(ItemStatus::nItemStatus);
}

Item :: ~Item()
{
    FreeItem();
}

const SDL_Rect Item :: GetRect()
{
    if (img.empty())
        cout << "Items has no frame or not been initialized\n";
    else
        return img[cur_frame].GetRect();
}

void Item :: SetRect(const int& x, const int& y)
{
    if (img.empty())
        cout << "Items has no frame or not been initialized\n";
    else
        img[cur_frame].SetRect(x, y);
}

/// [type][status]

void Item :: SetItem(const ItemType& _type, const ItemStatus& _status)
{
    if (type != uint16_t(_type) || status != uint16_t(_status))
    {
        type = uint16_t(_type);
        status = uint16_t(_status);
        img.resize(ItemFrame[type][status]);
        for(int i = 0; i < img.size(); ++i)
            img[i].LoadImg(ITEM_FOLDER + ItemTypeText[type] + '_' + ItemStatusText[status] + '_' + to_string(i) + ".png");
        cur_frame = 0;
        if (_status == ItemStatus::APPLY)
            LoadSound(apply_sound, SOUND_FOLDER + ItemTypeText[type] + "_apply.wav");
    }
    ///for(int i = 0; i < img.size(); ++i)
    ///    img[i].LoadImg(ITEM_FOLDER + ItemTypeText[type] + '_' + ItemStatusText[status] + '_' + to_string(i) + ".png");
}

void Item :: RenderItem()
{
    if (img.empty())
        return;
    ///cout << cur_frame << endl;
    ///img[cur_frame].LoadImg(ITEM_FOLDER + "coin_show_0.png");
    img[cur_frame].LoadImg(ITEM_FOLDER + ItemTypeText[type] + '_' + ItemStatusText[status] + '_' + to_string(cur_frame) + ".png");
    img[cur_frame].Render();
    if (++cur_frame == img.size())
        cur_frame = 0;
}

void Item :: RenderSound()
{
    switch (static_cast <ItemStatus>(status))
    {
        case ItemStatus::APPLY:
            PlaySound(apply_sound, 1);
            break;
        default:
            break;
    }
}


void Item :: FreeItem()
{
    Mix_FreeChunk(apply_sound);
    apply_sound = nullptr;
    for(auto& x : img)
        x.Free();
    img.clear();
    type = uint16_t(ItemType :: nItemType);
    status = uint16_t(ItemStatus::nItemStatus);
    cur_frame = 0;
}

#endif