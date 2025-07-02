#include <raylib.h>

#ifndef FROG_H
#define FROG_H

class Frog
{
protected:
    Texture2D sprite;
    Texture2D lilyPad;
    bool spriteLoaded;
    bool isFrog;
    bool active;

public:
    static double speed;

    float width, height;
    bool goldFrog;
    bool bullets;
    float x, y;
    int score;

    Frog(float _x, float _y, float _width, float _height, int _score);

    void die(bool moreDificulty);
    void draw();
    void update();
    void changeToType(bool _isFrog);

    void moreSpeed();
    void lessSpeed();
    static void resetSpeed();

    bool getIsFrog() const { return isFrog; }
    bool isActive() const { return active; }

    Rectangle getRect() const { return {x, y, width, height}; }
};

#endif