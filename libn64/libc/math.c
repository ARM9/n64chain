#include <math.h>

float sinf(float x) {
    const float B = 4/M_PI;
    const float C = -4/(M_PI*M_PI);
    float y = B * x + C * x * fabsf(x);
    #if EXTRA_PRECISION
    y = 0.225f * (y * fabsf(y) - y) + y;   // Q * y + P * y * abs(y)
    #endif
    return y;

    /*const float tp = 1.f/(2.f*M_PI);*/
    /*x *= tp;*/
    /*x -= .25f + floorf(x + .25f);*/
    /*x *= 16.f * (fabsf(x) - .5f);*/
    /*#if EXTRA_PRECISION*/
    /*x += .225f * x * (fabsf(x) - 1.f);*/
    /*#endif*/
    /*return x;*/
}

