//
// Created by wlucas-f on 4/16/26.
//

#ifndef MINIRT_INTERVAL_H
#define MINIRT_INTERVAL_H

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
#endif //MINIRT_INTERVAL_H