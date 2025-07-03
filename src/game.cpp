
#include "assets.h"
#include "game.h"

Game::Game(Player *_player, int _numFrogs, Assets *_assets)
    : assets(_assets), player(_player), numOfFrogs(_numFrogs)
{
    currentGameState = GAMEPLAY;
    numOfItems = 2;

    for (int i = 0; i < numOfFrogs; i++)
    {
        spawnFrog(player->getMunition());
    }

    for (int i = 0; i < numOfItems; i++)
    {
        spawnItem();
    }

    retryButton = {(float)screenWidth / 2 - 130, (float)screenHeight / 2 + 50, 260, 60};
}

void Game::spawnFrog(int bullets)
{
    Frog frog(randomInRange(-100, -600), randomInRange(60, screenHeight - 120), 64, 64, 5, assets);
    frog.goldFrog = false;
    frog.bullets = false;

    double randomValue = randomInRange(0.0, 1.0);
    if (randomValue < munitionProb(bullets))
    {
        frog.bullets = true;
        frog.score = 10;
    }
    else
    {
        if (randomValue < 0.1)
        {
            frog.goldFrog = true;
            frog.score = 25;
        }
        else if (randomValue < 0.2)
        {
            frog.changeToType(false);
            frog.score = -2;
        }
    }

    frogs.push_back(frog);
}

void Game::spawnItem()
{
    Item item(randomInRange(-100, -600), randomInRange(60, screenHeight - 120), 64, 64, assets);
    items.push_back(item);
}

void Game::ResetGame()
{
    numOfItems = 0;

    player->setMunition(10);
    player->setScore(0);
    player->setFrogsKilled(0);

    frogs.clear();
    items.clear();
    floatingTexts.clear();
    Frog::resetSpeed();

    for (int i = 0; i < numOfFrogs; i++)
    {
        spawnFrog(player->getMunition());
    }
}

void Game::handleGameplayLogic(float deltaTime)
{
    if (!IsMusicStreamPlaying(assets->themeSong))
    {
        SeekMusicStream(assets->themeSong, 0.0f);
        PlayMusicStream(assets->themeSong);
    }

    for (auto &frog : frogs)
    {
        frog.update();
        if (frog.x > screenWidth + frog.width)
        {
            spawnFrog(player->getMunition());
            frog.die(false);
        }
    }

    for (auto &item : items)
    {
        item.update();
        if (item.x > screenWidth + item.width)
        {
            item.clear(false);
            spawnItem();
        }
    }

    for (auto &text : floatingTexts)
    {
        text.update(deltaTime);
    }

    if (player->getMunition() <= 0)
    {
        currentGameState = GAMEOVER;
        PlaySound(assets->gameOverAudio);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && player->getMunition() > 0)
    {
        Vector2 mousePoint = GetMousePosition();
        bool hitSomething = false;

        for (auto &frog : frogs)
        {
            if (frog.isActive() && CheckCollisionPointRec(mousePoint, frog.getRect()))
            {
                hitSomething = true;

                Color textColor = WHITE;
                if (frog.getIsFrog())
                {
                    textColor = (frog.score > 0) ? GOLD : RED;
                    if (frog.bullets)
                    {
                        textColor = BLUE;
                    }
                }
                else
                {
                    textColor = GRAY;
                }

                Vector2 pos = (Vector2){frog.x + frog.width / 2, frog.y + frog.height / 2};
                floatingTexts.emplace_back(pos, frog.score, textColor, 1.5f);

                if (frog.bullets)
                {
                    Vector2 pos = (Vector2){frog.x + frog.width / 2, (frog.y + frog.height / 2) - 20};
                    floatingTexts.emplace_back(pos, 5, BROWN, 1.5f);
                }

                player->shot(frog.score);
                spawnFrog(player->getMunition());
                frog.die(true);

                if (frog.bullets)
                {
                    player->reload(5);
                }

                if (frog.getIsFrog())
                {
                    player->kill();
                }

                PlaySound(assets->frogAudio);
                break;
            }
        }

        for (auto &item : items)
        {
            if (item.isActive() && CheckCollisionPointRec(mousePoint, item.getRect()))
            {
                hitSomething = true;

                Vector2 pos = (Vector2){item.x + item.width / 2, item.y + item.height / 2};
                floatingTexts.emplace_back(pos, 6, GREEN, 1.5f);
                item.clear(true);
                spawnItem();

                // PlaySound(assets->frogAudio);
                break;
            }
        }

        if (!hitSomething)
        {
            player->shot(-1);
            Vector2 mousePoint = GetMousePosition();
            floatingTexts.emplace_back(mousePoint, -1, GRAY, 1.5f);
        }
    }

    frogs.erase(
        std::remove_if(
            frogs.begin(),
            frogs.end(), [](const Frog &frog)
            { return !frog.isActive(); }),
        frogs.end());

    floatingTexts.erase(
        std::remove_if(
            floatingTexts.begin(),
            floatingTexts.end(), [](const FloatingText &text)
            { return text.isFinished(); }),
        floatingTexts.end());
}

void Game::handleGameOverLogic()
{
    if (IsMusicStreamPlaying(assets->themeSong))
    {
        PauseMusicStream(assets->themeSong);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, retryButton))
        {
            ResetGame();
            currentGameState = GAMEPLAY;
        }
    }
}

void Game::handleGameplayGraphics()
{
    for (auto &frog : frogs)
    {
        frog.draw();
    }

    for (auto &item : items)
    {
        item.draw();
    }

    std::string scoreText = "Score: " + std::to_string(player->getScore());
    int scoreTextWidth = MeasureText(scoreText.c_str(), fontSize);
    int scorePositionX = (screenWidth / 2) - (scoreTextWidth / 2);

    std::string bulletsText = "Bullets: " + std::to_string(player->getMunition());
    int bulletsTextWidth = MeasureText(bulletsText.c_str(), fontSize);
    int bulletsPositionX = (screenWidth / 2) - (bulletsTextWidth / 2);

    DrawRectangle(0, 0, screenWidth, 50, BLACK);
    DrawRectangle(0, screenHeight - 50, screenWidth, 50, BLACK);
    DrawTextEx(assets->customFont, scoreText.c_str(), (Vector2){(float)scorePositionX, 10.0f}, fontSize, 0, WHITE);
    DrawTextEx(assets->customFont, bulletsText.c_str(), (Vector2){(float)bulletsPositionX, (float)(screenHeight - fontSize - 10)}, fontSize, 0, WHITE);

    for (auto &text : floatingTexts)
    {
        std::string valueStr = ((text.value > 0) ? "+" : "") + std::to_string(text.value);
        int textWidth = MeasureText(valueStr.c_str(), 20);
        DrawTextEx(assets->customFont, valueStr.c_str(), (Vector2){text.position.x - textWidth / 2, text.position.y}, 20, 0, text.getCurrentColor());
    }
}

void Game::handleGameOverGraphics()
{
    const char *retryText = "Play again";
    int retryTextFontSize = 30;
    int retryTextWidth = MeasureText(retryText, retryTextFontSize);

    DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);

    const char *gameOverText = "GAME OVER!";
    int gameOverTextWidth = MeasureText(gameOverText, 60);
    Vector2 gameOverTextPos = (Vector2){(float)((screenWidth / 2) - (gameOverTextWidth / 2)), (float)(screenHeight / 2 - 100)};
    DrawTextEx(assets->customFont, gameOverText, gameOverTextPos, fontSize * 2, 0, RED);

    std::string finalScoreText = "Score: " + std::to_string(player->getScore());
    int finalScoreTextWidth = MeasureText(finalScoreText.c_str(), fontSize);
    Vector2 finalScoreTextPos = (Vector2){(float)((screenWidth / 2) - (finalScoreTextWidth / 2)), (float)(screenHeight / 2 - 20)};
    DrawTextEx(assets->customFont, finalScoreText.c_str(), finalScoreTextPos, fontSize, 0, WHITE);

    std::string frogsKilledText = "Frogs: " + std::to_string(player->getFrogsKilled());
    int frogsKilledTextWidth = MeasureText(frogsKilledText.c_str(), fontSize);
    Vector2 frogsKilledTextPos = (Vector2){(float)((screenWidth / 2) - (frogsKilledTextWidth / 2)), (float)(screenHeight / 2 + 10)};
    DrawTextEx(assets->customFont, frogsKilledText.c_str(), frogsKilledTextPos, fontSize, 0, WHITE);

    DrawRectangleRec(retryButton, Fade(GREEN, 0.2f));
    Vector2 retryButtonPos = (Vector2){retryButton.x + (retryButton.width / 2) - (retryTextWidth / 2), retryButton.y + (retryButton.height / 2) - (retryTextFontSize / 2)};
    DrawTextEx(assets->customFont, retryText, retryButtonPos, retryTextFontSize, 0, WHITE);
}