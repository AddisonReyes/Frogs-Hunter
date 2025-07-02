#include <algorithm>
#include <random>

#include "utils.h"

double randomInRange(double min, double max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

double munitionProb(int bullets)
{
    double minProb = 0.01;
    double maxProb = 0.30;
    int minMunition = 2;
    int maxMunition = 20;

    double probability = maxProb - ((maxProb - minProb) * (bullets - minMunition) / (maxMunition - minMunition));

    probability = std::max(minProb, std::min(maxProb, probability));

    return probability;
}