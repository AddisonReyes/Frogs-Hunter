#include "game.h"

#include <raylib.h>
#include <iostream>
#include <vector>

int main()
{
    InitWindow(screenWidth, screenHeight, "Frogs Hunter!");
    InitAudioDevice();
    SetTargetFPS(60);

    InitFrogTextures();

    Player player(10);
    Game game(&player, 10);

    SetMusicVolume(themeSong, 0.5f);
    SetSoundVolume(gameOverAudio, 0.5f);
    SetSoundVolume(frogAudio, 0.5f);

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        UpdateMusicStream(themeSong);

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

    UnloadMusicStream(themeSong);
    UnloadSound(gameOverAudio);
    UnloadSound(frogAudio);
    UnloadFrogTextures();

    CloseAudioDevice();
    CloseWindow();
    return 0;
}