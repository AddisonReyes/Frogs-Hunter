#include "frog.h"
#include "player.h"

#include <raylib.h>
#include <iostream>
#include <vector>

int main()
{
    const Color bkgColor = {88, 225, 246, 255};

    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Frogs Hunter!");
    SetTargetFPS(60);

    Player player(10);

    std::vector<Frog> frogs;

    frogs.emplace_back(100, 100, 64, 64, 5);
    frogs.emplace_back(300, 250, 70, 70, 5);
    Frog stone1(500, 150, 80, 80, -2);
    stone1.changeToType(false);
    frogs.push_back(stone1);
    frogs.emplace_back(650, 400, 50, 50, 5);

    const int fontSize = 32;

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

                    if (frog.getIsFrog())
                    {
                        std::cout << "¡Sapo cazado!" << std::endl;
                        frog.setActive(false);
                        player.shot(frog.score);
                    }
                    else
                    {
                        std::cout << "¡Piedra golpeada!" << std::endl;
                        frog.setActive(false);
                        player.shot(frog.score);
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