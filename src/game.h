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

enum GameState
{
    GAMEPLAY,
    GAMEOVER
};

class Game
{
protected:
    Assets *assets;
    Player *player;
    std::vector<FloatingText> floatingTexts;
    std::vector<Frog> frogs;
    int numOfFrogs;

    Rectangle retryButton;

public:
    GameState currentGameState;
    Game(Player *player, int numFrogs, Assets *assets);

    void spawnFrog(int bullets);
    void ResetGame();

    void handleGameplayLogic(float deltaTime);
    void handleGameOverLogic();
    void handleGameplayGraphics();
    void handleGameOverGraphics();
};

#endif