#pragma once
#include "preincludes.h"

class Item
{

public:
    Item(std::string Name, List<Stat> Stats, std::string Slot)
    {
        _name = Name;
        _stats = Stats;
        _slot = Slot;
        _sessionItemId = next_session_item_id();
    }

    List<Stat> Stats() const { return _stats; }
    std::string Name() const { return _name; }
    std::string Slot() const { return _slot; }
    int SessionItemId() const { return _sessionItemId; }
private:
    List<Stat> _stats;
    std::string _name = "unknown";
    std::string _slot = "unknown";
    int _sessionItemId;
};


class ItemBase
{
public:
    ItemBase(std::string Name, List<PossibleStat> PossibleStats, std::string Slot)
    {
        _name = Name;
        copy(PossibleStats.begin(), PossibleStats.end(), std::back_inserter(_possibleStats));
        _slot = Slot;
    }

    List<PossibleStat> PossibleStats() const { return _possibleStats; }
    std::string Name() const { return _name; }
    std::string Slot() const { return _slot; }
private:
    List<PossibleStat> _possibleStats;
    std::string _name;
    std::string _slot;

};