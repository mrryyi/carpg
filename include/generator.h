#pragma once
#include "preincludes.h"
/*
Generates numbers and stats 
*/

int random_int_within_range(int min, int max) {
    return (rand() % abs(max - min)) + min;
}

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

Stat generate_stat(StatPossibility possibleStat)
{
    auto generatedNumber = random_number_within_range_with_step(possibleStat.RangeMin(),
        possibleStat.RangeMax(),
        possibleStat.Step());

    Stat generatedStat = Stat(possibleStat.Name(), generatedNumber);
    return generatedStat;
}

class Generator {
public:
    Generator() {
        _prefixes.push_back("Suffocating");
        _prefixes.push_back("Intoxicating");
        _prefixes.push_back("Scalding");
        _prefixes.push_back("Foxy");
        _prefixes.push_back("Intimidating");
        _prefixes.push_back("Bladed");
        _prefixes.push_back("Tusked");
        _prefixes.push_back("Bloody");

        // MIDDLE NAME
        _middle_names["head"] = std::vector<std::string>{ "headdress", "crown" };
        _middle_names["righthand"] = std::vector<std::string>{ "einhander", "monster-slayer" };
        _middle_names["lefthand"] = std::vector<std::string>{ "einhander", "monster-slayer" };
        _middle_names["chest"] = std::vector<std::string>{ "harness", "protector" };
        _middle_names["leftshoulder"] = std::vector<std::string>{ "mantle","amice" };
        _middle_names["rightshoulder"] = std::vector<std::string>{ "shoulderpads", "spaulder" };
        _middle_names["waist"] = std::vector<std::string>{ "belt", "waistguard", "waistwrap", "waistband" };
        _middle_names["neck"] = std::vector<std::string>{ "choker", "charm", "pendant", "necklace" };
        _middle_names["finger"] = std::vector<std::string>{ "signet", "ring" };
        _middle_names["legs"] = std::vector<std::string>{ "legguards", "pants" };
        _middle_names["wrist"] = std::vector<std::string>{ "bracers", "wristguards" };
        _middle_names["feet"] = std::vector<std::string>{ "shoes", "treads", "boots", "striders" };

        // SUFFIXES
        _suffixes.push_back("of the bear");
        _suffixes.push_back("of the sun");
        _suffixes.push_back("of the fox");
        _suffixes.push_back("of the monster");

        // SLOTS
        _slots.push_back("head");
        _slots.push_back("righthand");
        _slots.push_back("lefthand");
        _slots.push_back("chest");
        _slots.push_back("leftshoulder");
        _slots.push_back("rightshoulder");
        _slots.push_back("waist");
        _slots.push_back("neck");
        _slots.push_back("finger");
        _slots.push_back("legs");
        _slots.push_back("wrist");
        _slots.push_back("feet");

        // STATS
        // TODO
    }

    std::unique_ptr<ItemBase> generate_item_base() {


        std::string random_slot = _slots[random_int_within_range(0, _slots.size() - 1)];
        std::string random_middle_name = _middle_names[random_slot][random_int_within_range(0, _middle_names[random_slot].size() - 1)];
        std::string random_suffix = _suffixes[random_int_within_range(0, _suffixes.size() - 1)];
        std::string random_prefix = _prefixes[random_int_within_range(0, _prefixes.size() - 1)];

        std::string name = random_prefix + " " + random_middle_name + " " + random_suffix;
        std::vector<StatPossibility> stat_possibilities;
        stat_possibilities.push_back(StatPossibility("strength", 10, 100, 1));
        stat_possibilities.push_back(StatPossibility("vitality", 10, 100, 1));
        stat_possibilities.push_back(StatPossibility("intelligence", 10, 100, 1));

        return std::make_unique<ItemBase>(name, stat_possibilities, random_slot);
    }

private:
    std::vector<std::string> _slots;
    std::vector<std::string> _prefixes;
    std::unordered_map<std::string, std::vector<std::string>> _middle_names;
    std::vector<std::string> _suffixes;
};