#include "RandomHelper.h"


RandomHelper::InitRandom RandomHelper::ir;


int RandomHelper::GetInt(int max)
{
    return GetInt(0, max);
}


int RandomHelper::GetInt(int min, int max)
{
    return rand() % (1 + max - min) + min;
}


float RandomHelper::GetFloat(float max)
{
    return GetFloat(0, max);
}


float RandomHelper::GetFloat(float min, float max)
{
    return (((float)rand())/RAND_MAX) * (max - min) + min;
}
