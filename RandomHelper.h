#pragma once

#include <time.h>
#include <random>


class RandomHelper
{
private:
    class InitRandom
    {
    public:
        InitRandom()
        {
            srand(time(0));
        }
    };

    static InitRandom ir;

public:
    RandomHelper();
    ~RandomHelper();

    static int GetInt(int max);
    static int GetInt(int min, int max);
    static float GetFloat(float max);
    static float GetFloat(float min, float max);
};
