#pragma once
#include "preincludes.h"

class Generator {
private:
    SessionItems* _ref_sessionItems;
public:
    Generator(SessionItems* sessionItems) {
        _ref_sessionItems = sessionItems;
    }

    double RandomNumberWithinRangeWithStep(double rangeMin, double rangeMax, double step)
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

    Stat GenerateStat(PossibleStat possibleStat)
    {
        auto generatedNumber = RandomNumberWithinRangeWithStep(possibleStat.RangeMin(),
            possibleStat.RangeMax(),
            possibleStat.Step());

        Stat generatedStat = Stat(possibleStat.Name(), generatedNumber);
        return generatedStat;
    }

    Item GenerateItem(std::string name, List<PossibleStat> possibleStats, std::string slot) {
        List<Stat> generatedStats = List<Stat>();

        for (PossibleStat possibleStat : possibleStats) {
            generatedStats.push_back(GenerateStat(possibleStat));
        }
        unsigned int next_session_id = _ref_sessionItems->NextSessionId();

        debug_print("GenerateItem", std::to_string(next_session_id));
        Item item(name, generatedStats, slot, next_session_id);
        _ref_sessionItems->NewItem(item);

        return item;
    }

    Item GenerateItemWithBase(ItemBase itemBase) {
        return GenerateItem(itemBase.Name(), itemBase.PossibleStats(), itemBase.Slot());
    }

};
