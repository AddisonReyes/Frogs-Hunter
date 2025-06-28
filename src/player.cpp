#include "player.h"

Player::Player(int initialMunition)
{
    munition = initialMunition;
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