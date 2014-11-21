#ifndef CHOWDREN_MATH_H
#define CHOWDREN_MATH_H

#include <math.h>
#include <stdlib.h>
#include "crossrand.h"
#include <iostream>
#include <stdarg.h>
#include <boost/type_traits/common_type.hpp>
#include "dynnum.h"
#include <algorithm>

#define CHOW_PI 3.14159265358979323846264338327950288

// math helpers

inline float mod(float a, float b)
{
    return a - b * floor(a / b);
}

inline int wrap_range(int v, int a, int b)
{
    int range = b - a + 1;
    if (v < a)
        v += range * ((a - v) / range + 1);
    return a + (v - a) % range;
}

template <class T>
inline T rad(T x)
{
    return x * (CHOW_PI/180);
}

template <class T>
inline T deg(T x)
{
    return x * (180/CHOW_PI);
}

template <class T>
inline int sign_int(T x)
{
    if (x > 0)
        return 1;
    else if (x < 0)
        return -1;
    return 0;
}

inline double sin_deg(double x)
{
    return sin(rad(x));
}

inline double cos_deg(double x)
{
    return cos(rad(x));
}

inline double atan_deg(double v)
{
    return deg(atan(v));
}

inline double atan2_deg(double a, double b)
{
    return deg(atan2(a, b));
}

inline double asin_deg(double v)
{
    return deg(asin(v));
}

inline float get_length(float x, float y)
{
    return sqrt(x * x + y * y);
}

inline float get_distance(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    return get_length(dx, dy);
}

inline double get_angle(int x1, int y1, int x2, int y2)
{
    return atan2_deg(y2 - y1, x2 - x1);
}

inline double get_direction(int x1, int y1, int x2, int y2)
{
    return get_angle(x1, y1, x2, y2) / -11.25;
}

inline int get_direction_int(int x1, int y1, int x2, int y2)
{
    return int(get_direction(x1, y1, x2, y2));
}

inline int int_round(double d)
{
    // mmf behaviour
    int v = (int)floor(d + 0.5);
    if (d - v > 0.5)
        v++;
    return v;
}

inline int int_min(int value1, int value2)
{
    return std::min<int>(value1, value2);
}

inline int int_max(int value1, int value2)
{
    return std::max<int>(value1, value2);
}

template <class T, class U>
inline typename boost::common_type<T, U>::type get_min(T a, U b)
{
    return std::min<typename boost::common_type<T, U>::type>(a, b);
}

template <class T, class U>
inline typename boost::common_type<T, U>::type get_max(T a, U b)
{
    return std::max<typename boost::common_type<T, U>::type>(a, b);
}

template <class T>
inline T clamp(T value, T min, T max)
{
    return std::max(min, std::min(value, max));
}

template <class T>
inline T clamp(T val)
{
    return std::max<T>(0, std::min<T>(val, 1));
}

inline int get_abs(int v)
{
    return abs(v);
}

inline float get_abs(float v)
{
    return fabs(v);
}

inline double get_abs(double v)
{
    return fabs(v);
}

inline int get_ceil(int v)
{
    return v;
}

inline float get_ceil(float v)
{
    return ceil(v);
}

inline double get_ceil(double v)
{
    return ceil(v);
}

template <class T>
inline double get_exp(T v)
{
    return exp(double(v));
}

template <class T>
inline double get_log10(T v)
{
    return log10(double(v));
}

inline int get_floor(int v)
{
    return v;
}

inline float get_floor(float v)
{
    return floor(v);
}

inline double get_floor(double v)
{
    return floor(v);
}

inline void intersect(int a_x1, int a_y1, int a_x2, int a_y2,
                      int b_x1, int b_y1, int b_x2, int b_y2,
                      int & r_x1, int & r_y1, int & r_x2, int & r_y2)
{
    r_x1 = std::max<int>(a_x1, b_x1);
    r_y1 = std::max<int>(a_y1, b_y1);
    r_x2 = std::min<int>(a_x2, b_x2);
    r_y2 = std::min<int>(a_y2, b_y2);
}

inline bool collides(int a_x1, int a_y1, int a_x2, int a_y2,
                     int b_x1, int b_y1, int b_x2, int b_y2)
{
    return a_x2 > b_x1 && a_y2 > b_y1 && a_x1 < b_x2 && a_y1 < b_y2;
}

inline bool collides(int a[4], int b[4])
{
    return a[2] > b[0] && a[3] > b[1] && a[0] < b[2] && a[1] < b[3];
}

inline void rect_union(int a_x1, int a_y1, int a_x2, int a_y2,
                       int b_x1, int b_y1, int b_x2, int b_y2,
                       int & r_x1, int & r_y1, int & r_x2, int & r_y2)
{
    r_x1 = std::min<int>(a_x1, b_x1);
    r_y1 = std::min<int>(a_y1, b_y1);
    r_x2 = std::max<int>(a_x2, b_x2);
    r_y2 = std::max<int>(a_y2, b_y2);
}

inline void get_dir(int dir, double & x, double & y)
{
    double r = rad(dir * 11.25);
    x = cos(r);
    y = -sin(r);
}

inline void get_dir(int dir, float & x, float & y)
{
    float r = rad(dir * 11.25f);
    x = cos(r);
    y = -sin(r);
}

// random

inline int randrange(int range)
{
    if (range == 0)
        return 0;
    return cross_rand() / (CROSS_RAND_MAX / range + 1);
}

inline float randrange(float a, float b)
{
    return a + cross_rand() / (CROSS_RAND_MAX/(b-a));
}

inline bool random_chance(int a, int b)
{
    return randrange(b) < a;
}

inline int pick_random(int count, ...)
{
    if (count == 0)
        std::cout << "Invalid pick_random count!" << std::endl;
    va_list ap;
    va_start(ap, count);
    int picked_index = randrange(count);
    int value;
    for(int i = 0; i < count; i++) {
        if (i != picked_index)
            va_arg(ap, int);
        else
            value = va_arg(ap, int);
    }
    va_end(ap);
    return value;
}

inline int round_pow2(int x)
{
    if (x < 0)
        return 0;
    --x;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x+1;
}

#endif // CHOWDREN_MATH_H
