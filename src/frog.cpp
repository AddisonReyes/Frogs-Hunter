#include <raylib.h>
#include "assets.h"
#include "frog.h"

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
            lilyPad = Assets::lilyPadTexture;
            // Color color;
            if (goldFrog)
            {
                sprite = Assets::frog3Texture;
                // color = YELLOW;
            }
            else if (isFrog && !bullets)
            {
                sprite = Assets::frog1Texture;
                // color = GREEN;
            }
            else if (bullets)
            {
                sprite = Assets::frog2Texture;
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