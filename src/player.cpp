#include "player.h"

Player::Player(int initialMunition)
{
    munition = initialMunition;
    frogsKilled = 0;
    score = 0;
}

void Player::shot(int points)
{
    score += points;
    munition -= 1;
    if (munition < 0)
    {
        munition = 0;
    }
}

void Player::reload(int bullets)
{
    munition += bullets;
}

void Player::kill()
{
    frogsKilled += 1;
}