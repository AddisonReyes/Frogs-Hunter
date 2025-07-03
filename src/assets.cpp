#include <raylib.h>
#include "assets.h"

Assets::Assets()
{
    // Audio
    themeSong = LoadMusicStream("assets/audio/theme.wav");
    gameOverAudio = LoadSound("assets/audio/gameOver.wav");
    frogAudio = LoadSound("assets/audio/frog.wav");

    SetMusicVolume(themeSong, 0.5f);
    SetSoundVolume(gameOverAudio, 0.5f);
    SetSoundVolume(frogAudio, 0.5f);

    // Textures
    frog1Texture = LoadTexture("assets/sprites/frog1.png");
    frog2Texture = LoadTexture("assets/sprites/frog2.png");
    frog3Texture = LoadTexture("assets/sprites/frog3.png");
    lilyPadTexture = LoadTexture("assets/sprites/lilyPad.png");

    // Text
    customFont = LoadFont("assets/font/alagard.ttf");
}

void Assets::UnloadAssets()
{
    // Audio
    UnloadMusicStream(themeSong);
    UnloadSound(gameOverAudio);
    UnloadSound(frogAudio);

    // Textures
    UnloadTexture(frog1Texture);
    UnloadTexture(frog2Texture);
    UnloadTexture(frog3Texture);
    UnloadTexture(lilyPadTexture);

    // Text
    UnloadFont(customFont);
}