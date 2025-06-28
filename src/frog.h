#include <raylib.h>

#ifndef FROG_H
#define FROG_H

class Frog
{
protected:
    float x, y;
    float width, height;
    bool isFrog;
    bool active;

public:
    int score;

    Frog(float _x, float _y, float _width, float _height, int _score);

    void draw();
    void update();
    void changeToType(bool _isFrog);

    bool getIsFrog() const { return isFrog; }
    bool isActive() const { return active; }
    void setActive(bool state) { active = state; }

    Rectangle getRect() const { return {x, y, width, height}; }
};

#endif