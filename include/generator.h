#pragma once
#include "preincludes.h"
/*
Generates numbers and stats 
*/
double random_number_within_range_with_step(double rangeMin, double rangeMax, double step)
{
    if (rangeMax < rangeMin) {
        debug_print("RandomNumberWithinRangeWithStep",
            "Max < min mismatch, min = " + std::to_string(rangeMin) +
            ", max = " + std::to_string(rangeMax));

        return 0.0;
    }

    rangeMin *= 100;
    rangeMax *= 100;
    step *= 100;

    int difference = int(rangeMax - rangeMin);
    int randomWithinDifference = rand() % difference;
    double rounded = std::round((double)randomWithinDifference / step) * step;

    double generatedNumber = (rounded + rangeMin) / 100;
    return generatedNumber;
}

Stat generate_stat(PossibleStat possibleStat)
{
    auto generatedNumber = random_number_within_range_with_step(possibleStat.RangeMin(),
        possibleStat.RangeMax(),
        possibleStat.Step());

    Stat generatedStat = Stat(possibleStat.Name(), generatedNumber);
    return generatedStat;
}
