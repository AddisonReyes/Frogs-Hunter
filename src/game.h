#include <algorithm>
#include <raylib.h>
#include <iostream>
#include <functional>
#include <vector>

#include "player.h"
#include "utils.h"
#include "item.h"
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
    std::vector<Item> items;
    int numOfFrogs;
    int numOfItems;

    Rectangle retryButton;

public:
    GameState currentGameState;
    Game(Player *player, int numFrogs, Assets *assets);

    void spawnFrog(int bullets);
    void spawnItem();
    void ResetGame();

    void handleGameplayLogic(float deltaTime);
    void handleGameOverLogic();
    void handleGameplayGraphics();
    void handleGameOverGraphics();
};

struct DrawInfo
{
    float y;
    std::function<void()> drawFunc;
};

#endif