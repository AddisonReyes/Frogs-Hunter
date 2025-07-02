#include <raylib.h>

#ifndef UTILS_H
#define UTILS_H

struct FloatingText
{
    Vector2 position;
    int value;
    Color color;
    float lifeTime;
    float fadeTime;
    float currentLife;

    FloatingText(Vector2 pos, int val, Color col = WHITE, float lt = 1.0f)
        : position(pos), value(val), color(col), lifeTime(lt), fadeTime(lt * 0.7f), currentLife(0.0f) {}

    void update(float dt)
    {
        currentLife += dt;
        position.y -= 0.5f;
    }

    bool isFinished() const
    {
        return currentLife >= lifeTime;
    }

    Color getCurrentColor() const
    {
        if (currentLife >= fadeTime)
        {
            float alpha = 1.0f - ((currentLife - fadeTime) / (lifeTime - fadeTime));
            return Fade(color, alpha);
        }
        return color;
    }
};

double randomInRange(double min, double max);
double munitionProb(int bullets);

#endif