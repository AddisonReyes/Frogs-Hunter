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

double Frog::speed = 0.6;

void Frog::draw()
{
    if (active)
    {
        Color color;
        if (goldFrog)
        {
            color = YELLOW;
        }
        else if (isFrog && !bullets)
        {
            color = GREEN;
        }
        else if (bullets)
        {
            color = BROWN;
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
    x += speed + aditionalSpeed;
}

void Frog::moreSpeed()
{
    if (speed < 10)
    {
        speed += 0.03;
    }
}

void Frog::lessSpeed()
{
    if (speed > 2)
    {
        speed -= 0.03;
    }
}

void Frog::changeToType(bool _isFrog)
{
    isFrog = _isFrog;
}

void Frog::die(bool moreDificulty)
{
    active = false;
    if (isFrog)
    {
        if (moreDificulty)
        {
            moreSpeed();
        }
        else
        {
            lessSpeed();
        }
    }
}

void Frog::resetSpeed()
{
    speed = 0.6;
}