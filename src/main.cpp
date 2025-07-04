#include <raylib.h>
#include <iostream>
#include <vector>

#include "game.h"

int main()
{
    InitWindow(screenWidth, screenHeight, "Frogs Hunter!");
    InitAudioDevice();
    SetTargetFPS(60);

    Assets assets;
    int nomOfFrogs = 10;
    int startBullets = 10;
    Player player(startBullets);
    Game game(&player, nomOfFrogs, &assets);

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        UpdateMusicStream(assets.themeSong);

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

    assets.UnloadAssets();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}