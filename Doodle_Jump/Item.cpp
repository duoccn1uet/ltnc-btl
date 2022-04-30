#include "Item.h"

Item :: Item()
{
    type = uint16_t(ItemType :: nItemType);
    status = uint16_t(ItemStatus::nItemStatus);
}

Item :: ~Item()
{
    Mix_FreeChunk(apply_sound);
}

const SDL_Rect Item :: GetRect()
{
    if (img.empty())
        cout << "Items has no frame or not been initialized\n";
    else
        return img[frame_ptr].GetRect();
}

void Item :: SetRect(const int& x, const int& y)
{
    if (img.empty())
        cout << "Items has no frame or not been initialized\n";
    else
        img[frame_ptr].SetRect(x, y);
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
        frame_ptr = 0;
        if (_status == ItemStatus::APPLY)
        {
            LoadSound(apply_sound, SOUND_FOLDER + ItemTypeText[type] + "_apply.wav");
        }
        else
        {
            Mix_FreeChunk(apply_sound);
            apply_sound = nullptr;
        }
    }
    ///for(int i = 0; i < img.size(); ++i)
    ///    img[i].LoadImg(ITEM_FOLDER + ItemTypeText[type] + '_' + ItemStatusText[status] + '_' + to_string(i) + ".png");
}

void Item :: RenderItem()
{
    if (img.empty())
        return;
    ///cout << frame_ptr << endl;
    ///img[frame_ptr].LoadImg(ITEM_FOLDER + "coin_show_0.png");
    img[frame_ptr].LoadImg(ITEM_FOLDER + ItemTypeText[type] + '_' + ItemStatusText[status] + '_' + to_string(frame_ptr) + ".png");
    img[frame_ptr].Render();
    if (++frame_ptr == img.size())
        frame_ptr = 0;
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

