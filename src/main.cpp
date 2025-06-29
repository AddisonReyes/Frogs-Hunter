#include "frog.h"
#include "player.h"
#include "utils.h"

#include <raylib.h>
#include <iostream>
#include <vector>

const int screenHeight = 600;
const int screenWidth = 800;
const int fontSize = 32;

void spawnFrog(std::vector<Frog> *frogs, int bullets)
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

    frogs->push_back(frog);
}

void ResetGame(Player *player, std::vector<Frog> *frogs, int numOfFrogs, std::vector<FloatingText> *texts)
{
    player->setMunition(10);
    player->setScore(0);
    player->setFrogsKilled(0);

    frogs->clear();
    texts->clear();
    Frog::resetSpeed();
    for (int i = 0; i < numOfFrogs; i++)
    {
        spawnFrog(frogs, player->getMunition());
    }
}

int main()
{
    const Color bkgColor = {88, 225, 246, 255};

    InitWindow(screenWidth, screenHeight, "Frogs Hunter!");
    InitAudioDevice();
    SetTargetFPS(60);

    Player player(10);
    GameState currentGameState = GAMEPLAY;

    Music themeSong = LoadMusicStream("src/assets/audio/theme.wav");
    Sound frogAudio = LoadSound("src/assets/audio/frog.wav");
    Sound gameOverAudio = LoadSound("src/assets/audio/gameOver.wav");

    SetMusicVolume(themeSong, 0.5f);

    SetSoundVolume(gameOverAudio, 0.5f);
    SetSoundVolume(frogAudio, 0.5f);

    std::vector<FloatingText>
        floatingTexts;
    std::vector<Frog> frogs;
    int numOfFrogs = 10;

    for (int i = 0; i < numOfFrogs; i++)
    {
        spawnFrog(&frogs, player.getMunition());
    }

    Rectangle retryButton = {(float)screenWidth / 2 - 130, (float)screenHeight / 2 + 50, 260, 60};
    const char *retryText = "Play again";
    int retryTextFontSize = 30;
    int retryTextWidth = MeasureText(retryText, retryTextFontSize);

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        UpdateMusicStream(themeSong);

        switch (currentGameState)
        {
        case GAMEPLAY:
        {
            if (!IsMusicStreamPlaying(themeSong))
            {
                SeekMusicStream(themeSong, 0.0f);
                PlayMusicStream(themeSong);
            }

            /*
             * Update
             */
            for (auto &frog : frogs)
            {
                frog.update();
                if (frog.x > screenWidth + frog.width)
                {
                    spawnFrog(&frogs, player.getMunition());
                    frog.die(false);
                }
            }

            for (auto &text : floatingTexts)
            {
                text.update(deltaTime);
            }

            if (player.getMunition() <= 0)
            {
                currentGameState = GAMEOVER;
                PlaySound(gameOverAudio);
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && player.getMunition() > 0)
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
                            (Vector2){frog.x + frog.width / 2, frog.y + frog.height / 2}, // Position: center of the frog
                            frog.score,
                            textColor,
                            1.5f // Duration of 1.5 seconds
                        );
                        if (frog.bullets)
                        {
                            floatingTexts.emplace_back(
                                (Vector2){frog.x + frog.width / 2, (frog.y + frog.height / 2) - 20}, // Position: center of the frog
                                5,
                                BROWN,
                                1.5f // Duration of 1.5 seconds
                            );
                        }

                        player.shot(frog.score);
                        spawnFrog(&frogs, player.getMunition());
                        frog.die(true);

                        if (frog.bullets)
                        {
                            player.reload(5);
                        }

                        if (frog.getIsFrog())
                        {
                            player.kill();
                        }

                        PlaySound(frogAudio);
                        break;
                    }
                }

                if (!hitSomething)
                {
                    player.shot(-1);
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
        break;

        case GAMEOVER:
        {
            if (IsMusicStreamPlaying(themeSong))
            {
                PauseMusicStream(themeSong);
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mousePoint = GetMousePosition();
                if (CheckCollisionPointRec(mousePoint, retryButton))
                {
                    ResetGame(&player, &frogs, numOfFrogs, &floatingTexts);
                    currentGameState = GAMEPLAY;
                }
            }
        }
        break;
        }

        /*
         * Draw
         */
        BeginDrawing();
        ClearBackground(bkgColor);

        switch (currentGameState)
        {
        case GAMEPLAY:
        {
            for (auto &frog : frogs)
            {
                frog.draw();
            }

            std::string scoreText = "Score: " + std::to_string(player.getScore());
            int scoreTextWidth = MeasureText(scoreText.c_str(), fontSize);
            int scorePositionX = (screenWidth / 2) - (scoreTextWidth / 2);

            std::string bulletsText = "Bullets: " + std::to_string(player.getMunition());
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
        break;

        case GAMEOVER:
        {
            DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);

            const char *gameOverText = "GAME OVER!";
            int gameOverTextWidth = MeasureText(gameOverText, 60);
            DrawText(gameOverText, (screenWidth / 2) - (gameOverTextWidth / 2), screenHeight / 2 - 100, 60, RED);

            std::string finalScoreText = "Score: " + std::to_string(player.getScore());
            int finalScoreTextWidth = MeasureText(finalScoreText.c_str(), fontSize);
            DrawText(finalScoreText.c_str(), (screenWidth / 2) - (finalScoreTextWidth / 2), screenHeight / 2 - 20, fontSize, WHITE);

            std::string frogsKilledText = "Frogs: " + std::to_string(player.getFrogsKilled());
            int frogsKilledTextWidth = MeasureText(frogsKilledText.c_str(), fontSize);
            DrawText(frogsKilledText.c_str(), (screenWidth / 2) - (frogsKilledTextWidth / 2), screenHeight / 2 + 10, fontSize, WHITE);

            DrawRectangleRec(retryButton, Fade(GREEN, 0.2f));
            DrawText(retryText, retryButton.x + (retryButton.width / 2) - (retryTextWidth / 2),
                     retryButton.y + (retryButton.height / 2) - (retryTextFontSize / 2),
                     retryTextFontSize, WHITE);
        }
        break;
        }

        EndDrawing();
    }

    UnloadMusicStream(themeSong);
    UnloadSound(gameOverAudio);
    UnloadSound(frogAudio);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}