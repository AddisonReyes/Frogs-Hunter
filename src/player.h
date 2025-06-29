#ifndef PLAYER_H
#define PLAYER_H

class Player
{
protected:
    int munition;
    int frogsKilled;
    int score;

public:
    Player(int initialMunition);
    void shot(int points);
    void reload(int bullets);

    int getScore() const { return score; }
    int getMunition() const { return munition; }
    int getFrogsKilled() const { return frogsKilled; }

    void setMunition(int _munition) { munition = _munition; }
    void setFrogsKilled(int _frogsKilled) { frogsKilled = _frogsKilled; }
    void setScore(int _score) { score = _score; }

    void kill();
};

#endif