#pragma once
#include "preincludes.h"

static class Printer
{
public:

    static void PrintLine(std::string str) {
        std::cout << str << std::endl;
    }

    static void PrintTitle(std::string title) {
        PrintLine("-----------------------------");
        PrintLine("--------" + title + "--------");
        PrintLine("-----------------------------");
    }

    static std::string RemovePointIfLast(std::string str) {

        if (str.size() < 1)
            return str;

        if (str.back() == '.')
            return str.substr(0, str.size() - 1);
        else
            return str;
    }

    static std::string PrettyDouble(double d) {
        // https://stackoverflow.com/questions/13686482/c11-stdto-stringdouble-no-trailing-zeros
        std::string str = std::to_string(d);
        str = str.erase(str.find_last_not_of('0') + 1, std::string::npos);
        str = RemovePointIfLast(str);
        return str;
    }

    static std::string StatStringRepresentation(Stat stat) {
        std::string stringStat = stat.Name() + ": " + PrettyDouble(stat.Value());
        if (stat.Name() == "critchance")
            stringStat += '%';

        return stringStat;
    }

    static void PrintStat(Stat stat) {
        PrintLine(StatStringRepresentation(stat));
    }

    static void PrintItem(Item* item) {
        PrintLine("-------------");
        PrintLine("Name: " + item->Name());
        PrintLine("Session Item ID: " + std::to_string(item->SessionItemId()));
        for (auto stat : item->Stats())
            PrintStat(stat);
        PrintLine("-------------");
    }

    static void PrintSessionItems(SessionItems* sessionItems) {
        PrintTitle("SESSION ITEMS");

        for (auto item : sessionItems->Items())
            PrintItem(&item.second);

    }

    static void PrintInventory(Inventory* inventory) {
        PrintTitle("INVENTORY");
        for (auto& item : inventory->Items()) {
            PrintItem(item.second);
        }

    }

    static void PrintEquipment(Equipment* equipment) {
        PrintTitle("EQUIPMENT");
        for (auto slot : equipment->Slots())
            if (slot.second != nullptr)
                PrintLine(slot.first + ": " + slot.second->Name());

    }

    static void PrintEquipmentStats(Equipment* equipment) {
        PrintTitle("EQUIPMENT STATS");
        auto countedStats = equipment->CountStats();

        for (auto countedStat : countedStats)
            PrintStat(countedStat);
    }
};