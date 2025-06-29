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
    spriteLoaded = false;
}

double Frog::speed = 0.6;

void Frog::draw()
{
    if (active)
    {
        if (!spriteLoaded)
        {
            lilyPad = LoadTexture("src/assets/sprites/lily_pad.png");
            // Color color;
            if (goldFrog)
            {
                sprite = LoadTexture("src/assets/sprites/frog3.png");
                // color = YELLOW;
            }
            else if (isFrog && !bullets)
            {
                sprite = LoadTexture("src/assets/sprites/frog1.png");
                // color = GREEN;
            }
            else if (bullets)
            {
                sprite = LoadTexture("src/assets/sprites/frog2.png");
                // color = BROWN;
            }
            else
            {
                // color = GRAY;
            }
            spriteLoaded = true;
            // DrawRectangle(x, y, width, height, color);
        }
        DrawTexture(lilyPad, x, y + 10, WHITE);
        DrawTexture(sprite, x, y, WHITE);
    }
}

void Frog::update()
{
    x += speed;
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