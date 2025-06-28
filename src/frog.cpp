#include "frog.h"
#include <raylib.h>

Frog::Frog(float _x, float _y, float _width, float _height, int _score)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    isFrog = true;
    active = true;
    score = _score;
}

void Frog::draw()
{
    if (active)
    {
        Color color;
        if (isFrog)
        {
            color = GREEN;
        }
        else
        {
            color = GRAY;
        }
        DrawRectangle(x, y, width, height, color);
    }
}

void Frog::update()
{
}

void Frog::changeToType(bool _isFrog)
{
    isFrog = _isFrog;
}