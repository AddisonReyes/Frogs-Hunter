#include <random>
#include <chrono>
#include "item.h"

Item::Item(float _x, float _y, float _width, float _height, Assets *_assets)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    active = true;
    spriteLoaded = false;
    assets = _assets;

    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    std::uniform_int_distribution<int> distribution(0, ItemType::COUNT - 1);
    int randomValue = distribution(generator);
    item = static_cast<ItemType>(randomValue);
}

double Item::speed = 0.6;

void Item::draw()
{
    if (active)
    {
        switch (item)
        {
        case ALCOHOL:
            break;
        case UNLIMITED_MUNITION:
            break;
        case NUCLEAR_BOMB:
            break;
        case MUNITION:
            break;
        case HEARTH:
            break;
        case HOURGLASS:
            break;
        case COUNT:
            break;
        }
        spriteLoaded = true;
    }

    // DrawTexture(lilyPad, x, y + 10, WHITE);
    // DrawTexture(sprite, x, y, WHITE);
    DrawRectangle(x, y, width, height, BLACK);
}

void Item::update()
{
    x += speed;
}

void Item::clear(bool moreDificulty)
{
    active = false;
    if (moreDificulty)
    {
        moreSpeed();
    }
    else
    {
        lessSpeed();
    }
}

void Item::moreSpeed()
{
    if (speed < 10)
    {
        speed += 0.03;
    }
}

void Item::lessSpeed()
{
    if (speed > 2)
    {
        speed -= 0.03;
    }
}

void Item::resetSpeed()
{
    speed = 0.6;
}