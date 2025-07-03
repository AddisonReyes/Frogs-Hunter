#include <raylib.h>
#include "assets.h"

#ifndef ITEM_H
#define ITEM_H

enum ItemType
{
    ALCOHOL,
    UNLIMITED_MUNITION,
    NUCLEAR_BOMB,
    MUNITION,
    HEARTH,
    HOURGLASS,
    COUNT
};

class Item
{
protected:
    Texture2D sprite;
    Texture2D lilyPad;
    Assets *assets;
    ItemType item;

    bool spriteLoaded;
    bool active;

public:
    static double speed;

    float width, height;
    float x, y;

    Item(float _x, float _y, float _width, float _height, Assets *_assets);

    void draw();
    void update();
    void clear(bool moreDificulty);

    void moreSpeed();
    void lessSpeed();
    static void resetSpeed();

    Rectangle getRect() const { return {x, y, width, height}; }
    void setType(ItemType newType) { item = newType; }
    bool isActive() const { return active; }
    ItemType getType() const { return item; }
};

#endif