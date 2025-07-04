#include <raylib.h>
#include "assets.h"
#include "frog.h"

Frog::Frog(float _x, float _y, float _width, float _height, int _score, Assets *_assets)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
    isFrog = true;
    active = true;
    score = _score;
    spriteLoaded = false;
    assets = _assets;
    extraSpeed = 0;
}

double Frog::speed = 0.6;

void Frog::draw()
{
    if (active)
    {
        if (!spriteLoaded)
        {
            lilyPad = assets->lilyPadTexture;

            if (goldFrog)
            {
                sprite = assets->frog3Texture;
            }
            else if (isFrog && !bullets)
            {
                sprite = assets->frog1Texture;
            }
            else if (bullets)
            {
                sprite = assets->frog2Texture;
            }

            spriteLoaded = true;
        }
        DrawTexture(lilyPad, x, y + 10, WHITE);
        DrawTexture(sprite, x, y, WHITE);
    }
}

void Frog::update()
{
    x += speed + extraSpeed;
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