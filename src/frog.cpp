#include "frog.h"
#include <raylib.h>

Texture2D Frog::frog1Texture = {0};
Texture2D Frog::frog2Texture = {0};
Texture2D Frog::frog3Texture = {0};
Texture2D Frog::lily_padTexture = {0};
double Frog::speed = 0.6;

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

void InitFrogTextures()
{
    Frog::frog1Texture = LoadTexture("assets/sprites/frog1.png");
    Frog::frog2Texture = LoadTexture("assets/sprites/frog2.png");
    Frog::frog3Texture = LoadTexture("assets/sprites/frog3.png");
    Frog::lily_padTexture = LoadTexture("assets/sprites/lily_pad.png");
}

void UnloadFrogTextures()
{
    UnloadTexture(Frog::frog1Texture);
    UnloadTexture(Frog::frog2Texture);
    UnloadTexture(Frog::frog3Texture);
    UnloadTexture(Frog::lily_padTexture);
}

void Frog::draw()
{
    if (active)
    {
        if (!spriteLoaded)
        {
            lilyPad = lily_padTexture;
            // Color color;
            if (goldFrog)
            {
                sprite = frog3Texture;
                // color = YELLOW;
            }
            else if (isFrog && !bullets)
            {
                sprite = frog1Texture;
                // color = GREEN;
            }
            else if (bullets)
            {
                sprite = frog2Texture;
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