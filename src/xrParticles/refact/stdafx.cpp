#include "stdafx.h"

float NRand(float sigma)
{
    if (sigma == 0)
    {
        return 0;
    }

    float y = 0.f;
    do
    {
        y = -logf(::Random.randF());
    } while (::Random.randF() > expf(-_sqr(y - 1.0f) * 0.5f));

    float resultY = rand() & 0x1
        ? y
        : -y;

    return resultY * sigma * ONE_OVER_SIGMA_EXP;
}