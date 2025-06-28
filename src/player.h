#ifndef PLAYER_H
#define PLAYER_H

class Player
{
protected:
    int munition;
    int score;

public:
    Player(int initialMunition);
    void shot(int points);
    void reload(int bullets);

    int getScore() const { return score; }
    int getMunition() const { return munition; }
};

#endif