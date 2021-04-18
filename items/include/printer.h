#pragma once
#include "preincludes.h"

static class Printer
{
public:

    static void PrintLine(std::string str) {
        std::cout << str << std::endl;
    }

    static std::string StatStringRepresentation(Stat stat) {
        std::string stringStat = stat.Name() + ": " + std::to_string(stat.Value());
        if (stat.Name() == "critchance")
            stringStat += '%';

        return stringStat;
    }

    static void PrintStat(Stat stat) {
        PrintLine(StatStringRepresentation(stat));
    }

    static void PrintInventory(Inventory* inventory) {
        PrintLine("-----------------------------");
        PrintLine("INVENTORY");
        for (auto item : inventory->Items()) {
            PrintLine(item->Name() + ':');
            for (auto stat : item->Stats())
                PrintStat(stat);
            PrintLine("");
        };

        PrintLine("-----------------------------");
    }

    static void PrintEquipment(Equipment* equipment) {
        PrintLine("-----------------------------");
        PrintLine("EQUIPMENT");
        for (auto slot : equipment->Slots())
            if (slot.second != nullptr)
                PrintLine(slot.first + ": " + slot.second->Name());

        PrintLine("-----------------------------");
    }

    static void PrintEquipmentStats(Equipment* equipment) {
        auto countedStats = equipment->CountStats();

        PrintLine("-----------------------------");
        PrintLine("EQUIPMENT STATS");
        for (auto countedStat : countedStats)
            PrintLine(countedStat.Name() + ':' + std::to_string(countedStat.Value()));
        PrintLine("-----------------------------");

    }
};