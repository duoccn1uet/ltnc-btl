#ifndef MAP_H
#define MAP_H

#include "CommonFunc.h"
#include "Platform.h"
#include "Character.h"

const int d_scroll_boundline = SCREEN_HEIGHT / 4;

class Map
{
public:

    Map();
    Map(Platform* _platform, Character* _character);
    ~Map();

    void LoadPlatform(Platform* _platform) {d_platforms = _platform;}
    void LoadCharacter(Character* _character) {d_character = _character;}
    int SrcollMap(const string& MAP_NAME);

private:
    Platform* d_platforms;
    Character* d_character;
};
#endif // MAP_H
