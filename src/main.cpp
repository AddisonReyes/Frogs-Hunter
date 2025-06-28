#include "frog.h"
#include "player.h"

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

void spawnFrog(std::vector<Frog> *frogs)
{
    Frog frog(randomInRange(50, screenWidth - 50), randomInRange(100, screenHeight - 100), 64, 64, 5);

    double randomValue = randomInRange(0.0, 1.0);
    if (randomValue < 0.10)
    {
        frog.changeToType(false);
        frog.bullets = true;
        frog.score = -2;
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
    for (int i = 0; i < 6; i++)
    {
        spawnFrog(&frogs);
    }

    while (!WindowShouldClose())
    {
        /*
         * Update
         */
        for (auto &frog : frogs)
        {
            frog.update();
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
                    frog.setActive(false);
                    player.shot(frog.score);
                    spawnFrog(&frogs);
                    if (frog.bullets)
                    {
                        player.reload(5);
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

        DrawText(scoreText.c_str(), scorePositionX, 10, fontSize, BLACK);
        DrawText(bulletsText.c_str(), bulletsPositionX, screenHeight - fontSize, fontSize, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}