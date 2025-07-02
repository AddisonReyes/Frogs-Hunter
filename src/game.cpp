
#include "assets.h"
#include "game.h"

Game::Game(Player *_player, int numFrogs) : player(_player)
{
    currentGameState = GAMEPLAY;
    numOfFrogs = numFrogs;

    for (int i = 0; i < numOfFrogs; i++)
    {
        spawnFrog(player->getMunition());
    }

    retryButton = {(float)screenWidth / 2 - 130, (float)screenHeight / 2 + 50, 260, 60};
}

void Game::spawnFrog(int bullets)
{
    Frog frog(randomInRange(-100, -600), randomInRange(60, screenHeight - 120), 64, 64, 5);
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

void Game::ResetGame()
{
    player->setMunition(10);
    player->setScore(0);
    player->setFrogsKilled(0);

    frogs.clear();
    floatingTexts.clear();
    Frog::resetSpeed();
    for (int i = 0; i < numOfFrogs; i++)
    {
        spawnFrog(player->getMunition());
    }
}

void Game::handleGameplayLogic(float deltaTime)
{
    if (!IsMusicStreamPlaying(Assets::themeSong))
    {
        SeekMusicStream(Assets::themeSong, 0.0f);
        PlayMusicStream(Assets::themeSong);
    }

    /*
     * Update
     */
    for (auto &frog : frogs)
    {
        frog.update();
        if (frog.x > screenWidth + frog.width)
        {
            spawnFrog(player->getMunition());
            frog.die(false);
        }
    }

    for (auto &text : floatingTexts)
    {
        text.update(deltaTime);
    }

    if (player->getMunition() <= 0)
    {
        currentGameState = GAMEOVER;
        PlaySound(Assets::gameOverAudio);
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

                floatingTexts.emplace_back(
                    (Vector2){frog.x + frog.width / 2, frog.y + frog.height / 2},
                    frog.score,
                    textColor,
                    1.5f);
                if (frog.bullets)
                {
                    floatingTexts.emplace_back(
                        (Vector2){frog.x + frog.width / 2, (frog.y + frog.height / 2) - 20},
                        5,
                        BROWN,
                        1.5f);
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

                PlaySound(Assets::frogAudio);
                break;
            }
        }

        if (!hitSomething)
        {
            player->shot(-1);
            Vector2 mousePoint = GetMousePosition();
            floatingTexts.emplace_back(
                mousePoint,
                -1,
                GRAY,
                1.5f);
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
    if (IsMusicStreamPlaying(Assets::themeSong))
    {
        PauseMusicStream(Assets::themeSong);
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

    std::string scoreText = "Score: " + std::to_string(player->getScore());
    int scoreTextWidth = MeasureText(scoreText.c_str(), fontSize);
    int scorePositionX = (screenWidth / 2) - (scoreTextWidth / 2);

    std::string bulletsText = "Bullets: " + std::to_string(player->getMunition());
    int bulletsTextWidth = MeasureText(bulletsText.c_str(), fontSize);
    int bulletsPositionX = (screenWidth / 2) - (bulletsTextWidth / 2);

    DrawRectangle(0, 0, screenWidth, 50, BLACK);
    DrawRectangle(0, screenHeight - 50, screenWidth, 50, BLACK);
    DrawText(scoreText.c_str(), scorePositionX, 10, fontSize, WHITE);
    DrawText(bulletsText.c_str(), bulletsPositionX, screenHeight - fontSize - 10, fontSize, WHITE);

    for (auto &text : floatingTexts)
    {
        std::string valueStr = ((text.value > 0) ? "+" : "") + std::to_string(text.value);
        int textWidth = MeasureText(valueStr.c_str(), 20);
        DrawText(valueStr.c_str(), text.position.x - textWidth / 2, text.position.y, 20, text.getCurrentColor());
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
    DrawText(gameOverText, (screenWidth / 2) - (gameOverTextWidth / 2), screenHeight / 2 - 100, 60, RED);

    std::string finalScoreText = "Score: " + std::to_string(player->getScore());
    int finalScoreTextWidth = MeasureText(finalScoreText.c_str(), fontSize);
    DrawText(finalScoreText.c_str(), (screenWidth / 2) - (finalScoreTextWidth / 2), screenHeight / 2 - 20, fontSize, WHITE);

    std::string frogsKilledText = "Frogs: " + std::to_string(player->getFrogsKilled());
    int frogsKilledTextWidth = MeasureText(frogsKilledText.c_str(), fontSize);
    DrawText(frogsKilledText.c_str(), (screenWidth / 2) - (frogsKilledTextWidth / 2), screenHeight / 2 + 10, fontSize, WHITE);

    DrawRectangleRec(retryButton, Fade(GREEN, 0.2f));
    DrawText(retryText, retryButton.x + (retryButton.width / 2) - (retryTextWidth / 2),
             retryButton.y + (retryButton.height / 2) - (retryTextFontSize / 2),
             retryTextFontSize, WHITE);
}