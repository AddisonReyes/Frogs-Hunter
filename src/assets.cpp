#include <raylib.h>
#include "assets.h"

// Audio
Music Assets::themeSong = {0};
Sound Assets::frogAudio = {0};
Sound Assets::gameOverAudio = {0};

// Textures
Texture2D Assets::frog1Texture = {0};
Texture2D Assets::frog2Texture = {0};
Texture2D Assets::frog3Texture = {0};
Texture2D Assets::lilyPadTexture = {0};

void InitAssets()
{
    // Audio
    Assets::themeSong = LoadMusicStream("assets/audio/theme.wav");
    Assets::gameOverAudio = LoadSound("assets/audio/gameOver.wav");
    Assets::frogAudio = LoadSound("assets/audio/frog.wav");

    SetMusicVolume(Assets::themeSong, 0.5f);
    SetSoundVolume(Assets::gameOverAudio, 0.5f);
    SetSoundVolume(Assets::frogAudio, 0.5f);

    // Textures
    Assets::frog1Texture = LoadTexture("assets/sprites/frog1.png");
    Assets::frog2Texture = LoadTexture("assets/sprites/frog2.png");
    Assets::frog3Texture = LoadTexture("assets/sprites/frog3.png");
    Assets::lilyPadTexture = LoadTexture("assets/sprites/lilyPad.png");
}

void UnloadAssets()
{
    // Audio
    UnloadMusicStream(Assets::themeSong);
    UnloadSound(Assets::gameOverAudio);
    UnloadSound(Assets::frogAudio);

    // Textures
    UnloadTexture(Assets::frog1Texture);
    UnloadTexture(Assets::frog2Texture);
    UnloadTexture(Assets::frog3Texture);
    UnloadTexture(Assets::lilyPadTexture);
}