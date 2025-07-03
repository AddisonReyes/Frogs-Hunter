#include <raylib.h>

#ifndef ASSETS_H
#define ASSETS_H

class Assets
{
public:
    Assets();
    void UnloadAssets();

    // Audio
    Music themeSong;
    Sound frogAudio;
    Sound gameOverAudio;

    // Textures
    Texture2D frog2Texture;
    Texture2D frog1Texture;
    Texture2D frog3Texture;
    Texture2D lilyPadTexture;

    // Text
    Font customFont;
};

#endif