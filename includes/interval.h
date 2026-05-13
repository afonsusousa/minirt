//
// Created by wlucas-f on 4/16/26.
//

#ifndef MINIRT_INTERVAL_H
#define MINIRT_INTERVAL_H

#include <stdbool.h>

typedef struct s_interval
{
    double min;
    double max;
} t_interval;

static inline double interval_size(t_interval interval)
{
    return (interval.max - interval.min);
}

static inline bool contains(t_interval interval, double value)
{
    return (interval.min <= value && value <= interval.max);
}

static inline bool surrounds(t_interval interval, double value)
{
    return (interval.min < value && value < interval.max);
}

static inline double interval_clamp(t_interval interval, double x)
{
    if (x < interval.min) return interval.min;
    if (x > interval.max) return interval.max;
    return x;
}

#endif //MINIRT_INTERVAL_H