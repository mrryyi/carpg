#pragma once
#include "preincludes.h"

namespace Generator {

    static double RandomNumberWithinRangeWithStep(double rangeMin, double rangeMax, double step)
    {
        if (rangeMax < rangeMin) {
            std::string error_message = "RandomNumberWithinRangeWithStep ERROR:";
            error_message += "Max range: " + std::to_string(rangeMin) + " above min range." + std::to_string(rangeMin);
            debug_print("Generator:RandomNumberWithinRangeWithStep",
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

    static Stat GenerateStat(PossibleStat possibleStat)
    {
        auto generatedNumber = RandomNumberWithinRangeWithStep(possibleStat.RangeMin(),
            possibleStat.RangeMax(),
            possibleStat.Step());

        Stat generatedStat = Stat(possibleStat.Name(), generatedNumber);
        return generatedStat;
    }

    static Item GenerateItem(std::string name, List<PossibleStat> possibleStats, std::string slot) {
        List<Stat> generatedStats = List<Stat>();

        for (PossibleStat possibleStat : possibleStats) {
            generatedStats.push_back(GenerateStat(possibleStat));
        }

        return Item(name, generatedStats, slot);
    }

    static Item GenerateItemWithBase(ItemBase itemBase) {
        return GenerateItem(itemBase.Name(), itemBase.PossibleStats(), itemBase.Slot());
    }

};
