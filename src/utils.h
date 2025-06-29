#include <random>
#include <algorithm>
#include <raylib.h>

#ifndef UTILS_H
#define UTILS_H

enum GameState
{
    GAMEPLAY,
    GAMEOVER
};

struct FloatingText
{
    Vector2 position;
    int value;
    Color color;
    float lifeTime;    // Time in seconds the text will be visible
    float fadeTime;    // Time when fading starts (optional, for smooth disappearance)
    float currentLife; // Current time passed since creation

    FloatingText(Vector2 pos, int val, Color col = WHITE, float lt = 1.0f)
        : position(pos), value(val), color(col), lifeTime(lt), fadeTime(lt * 0.7f), currentLife(0.0f) {}

    void update(float dt)
    {
        currentLife += dt;
        // Optionally, make it float upwards slightly
        position.y -= 0.5f; // Adjust this value for desired speed
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
            return Fade(color, alpha); // Raylib's Fade function
        }
        return color;
    }
};

double randomInRange(double min, double max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

double munitionProb(int bullets)
{
    double minProb = 0.01;
    double maxProb = 0.30;
    int minMunition = 1;
    int maxMunition = 15;

    double probability = maxProb - ((maxProb - minProb) * (bullets - minMunition) / (maxMunition - minMunition));

    probability = std::max(minProb, std::min(maxProb, probability));

    return probability;
}

#endif