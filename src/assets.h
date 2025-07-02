#include <raylib.h>

#ifndef ASSETS_H
#define ASSETS_H

class Assets
{
public:
    // Audio
    static Music themeSong;
    static Sound frogAudio;
    static Sound gameOverAudio;

    // Textures
    static Texture2D frog2Texture;
    static Texture2D frog1Texture;
    static Texture2D frog3Texture;
    static Texture2D lilyPadTexture;
};

#endif