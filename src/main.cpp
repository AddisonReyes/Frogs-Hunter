#include "frog.h"
#include "player.h"

#include <algorithm>
#include <raylib.h>
#include <iostream>
#include <random>
#include <vector>

const int screenHeight = 600;
const int screenWidth = 800;
const int fontSize = 32;

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

void spawnFrog(std::vector<Frog> *frogs, int bullets)
{
    Frog frog(randomInRange(-100, -300), randomInRange(60, screenHeight - 120), 64, 64, 5);
    frog.aditionalSpeed = randomInRange(0, 1);
    frog.goldFrog = false;
    frog.bullets = false;

    double randomValue = randomInRange(0.0, 1.0);
    if (randomValue < munitionProb(bullets))
    {
        frog.bullets = true;
        frog.score = 10;
    }
    else
    {
        if (randomValue < 0.1)
        {
            frog.goldFrog = true;
            frog.score = 25;
        }
        else if (randomValue < 0.2)
        {
            frog.changeToType(false);
            frog.score = -2;
        }
    }

    frogs->push_back(frog);
}

int main()
{
    const Color bkgColor = {88, 225, 246, 255};

    InitWindow(screenWidth, screenHeight, "Frogs Hunter!");
    SetTargetFPS(60);

    Player player(10);

    std::vector<Frog> frogs;
    int numOfFrogs = 10;

    for (int i = 0; i < numOfFrogs; i++)
    {
        spawnFrog(&frogs, player.getMunition());
    }

    while (!WindowShouldClose())
    {

        /*
         * Update
         */
        for (auto &frog : frogs)
        {
            frog.update();
            if (frog.x > screenWidth + frog.width)
            {
                spawnFrog(&frogs, player.getMunition());
                frog.die(false);
            }
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && player.getMunition() > 0)
        {
            Vector2 mousePoint = GetMousePosition();
            bool hitSomething = false;

            for (auto &frog : frogs)
            {
                if (frog.isActive() && CheckCollisionPointRec(mousePoint, frog.getRect()))
                {
                    hitSomething = true;
                    player.shot(frog.score);
                    spawnFrog(&frogs, player.getMunition());
                    frog.die(true);

                    if (frog.bullets)
                    {
                        player.reload(5);
                    }

                    if (frog.getIsFrog())
                    {
                        player.kill();
                    }

                    break;
                }
            }

            if (!hitSomething)
            {
                std::cout << "¡Clic en el agua! (nada tocado)" << std::endl;
                player.shot(-1);
            }
        }

        frogs.erase(
            std::remove_if(
                frogs.begin(),
                frogs.end(), [](const Frog &frog)
                { return !frog.isActive(); }),
            frogs.end());

        /*
         * Draw
         */
        BeginDrawing();
        ClearBackground(bkgColor);

        for (auto &frog : frogs)
        {
            frog.draw();
        }

        std::string scoreText = "Score: " + std::to_string(player.getScore());
        int scoreTextWidth = MeasureText(scoreText.c_str(), fontSize);
        int scorePositionX = (screenWidth / 2) - (scoreTextWidth / 2);

        std::string bulletsText = "Bullets: " + std::to_string(player.getMunition());
        int bulletsTextWidth = MeasureText(bulletsText.c_str(), fontSize);
        int bulletsPositionX = (screenWidth / 2) - (bulletsTextWidth / 2);

        DrawRectangle(0, 0, screenWidth, 50, BLACK);
        DrawRectangle(0, screenHeight - 50, screenWidth, 50, BLACK);
        DrawText(scoreText.c_str(), scorePositionX, 10, fontSize, WHITE);
        DrawText(bulletsText.c_str(), bulletsPositionX, screenHeight - fontSize - 10, fontSize, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}