#include <algorithm>
#include <raylib.h>
#include <iostream>
#include <vector>

#include "player.h"
#include "assets.h"
#include "utils.h"
#include "frog.h"

#ifndef GAME_H
#define GAME_H

extern void UnloadFrogTextures();
extern void InitFrogTextures();

const Color bkgColor = {88, 225, 246, 255};
const int screenHeight = 600;
const int screenWidth = 800;
const int fontSize = 32;

enum GameState
{
    GAMEPLAY,
    GAMEOVER
};

class Game
{
protected:
    Player *player;
    std::vector<FloatingText> floatingTexts;
    std::vector<Frog> frogs;
    int numOfFrogs;

    Rectangle retryButton;

public:
    GameState currentGameState;
    Game(Player *player, int numFrogs);

    void spawnFrog(int bullets);
    void ResetGame();

    void handleGameplayLogic(float deltaTime);
    void handleGameOverLogic();
    void handleGameplayGraphics();
    void handleGameOverGraphics();
};

#endif