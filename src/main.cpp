#include <raylib.h>
#include <iostream>
#include <vector>

#include "assets.h"
#include "game.h"

extern void UnloadAssets();
extern void InitAssets();

int main()
{
    InitWindow(screenWidth, screenHeight, "Frogs Hunter!");
    InitAudioDevice();
    SetTargetFPS(60);
    InitAssets();

    Player player(10);
    Game game(&player, 10);

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        UpdateMusicStream(Assets::themeSong);

        BeginDrawing();
        ClearBackground(bkgColor);
        switch (game.currentGameState)
        {
        case GAMEPLAY:
            game.handleGameplayLogic(deltaTime);
            game.handleGameplayGraphics();
            break;

        case GAMEOVER:
            game.handleGameOverLogic();
            game.handleGameOverGraphics();
            break;
        }

        EndDrawing();
    }

    UnloadAssets();

    CloseAudioDevice();
    CloseWindow();
    return 0;
}