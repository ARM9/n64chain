#include <math.h>

float sinf(float x) {
    const float B = 4/M_PI;
    const float C = -4/(M_PI*M_PI);
    float y = B * x + C * x * fabsf(x);
    /*const float P = 0.225;*/
    /*y = P * (y * fabsf(y) - y) + y;   // Q * y + P * y * abs(y)*/
    return y;
}

