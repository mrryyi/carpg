#pragma once
#include "preincludes.h"

class Equipment
{

public:
    Equipment()
    {
        _slots = std::map<std::string, Item*>();
        _slots.insert(std::pair<std::string, Item*>("head", nullptr));
        _slots.insert(std::pair<std::string, Item*>("lefthand", nullptr));
        _slots.insert(std::pair<std::string, Item*>("righthand", nullptr));
        _slots.insert(std::pair<std::string, Item*>("chest", nullptr));
        _slots.insert(std::pair<std::string, Item*>("leftshoulder", nullptr));
        _slots.insert(std::pair<std::string, Item*>("rightshoulder", nullptr));
        _slots.insert(std::pair<std::string, Item*>("belt", nullptr));
        _slots.insert(std::pair<std::string, Item*>("neck", nullptr));
        _slots.insert(std::pair<std::string, Item*>("finger1", nullptr));
        _slots.insert(std::pair<std::string, Item*>("finger2", nullptr));
        _slots.insert(std::pair<std::string, Item*>("finger3", nullptr));
        _slots.insert(std::pair<std::string, Item*>("finger4", nullptr));
        _slots.insert(std::pair<std::string, Item*>("legs", nullptr));
        _slots.insert(std::pair<std::string, Item*>("waist", nullptr));
        _slots.insert(std::pair<std::string, Item*>("leftwrist", nullptr));
        _slots.insert(std::pair<std::string, Item*>("rightwrist", nullptr));
        _slots.insert(std::pair<std::string, Item*>("leftfoot", nullptr));
        _slots.insert(std::pair<std::string, Item*>("rightfoot", nullptr));

        _slotMappings.insert(
            {
                { "hand", std::unordered_set<std::string> { "lefthand", "righthand" } },
                { "ring", std::unordered_set<std::string> { "ring1", "ring2", "ring3", "ring4"} },
                { "foot", std::unordered_set<std::string> { "leftfoot", "rightfoot"} },
                { "wrist", std::unordered_set<std::string> { "leftwrist", "rightwrist" } }
            }
        );
    }

    bool HasSlot(std::string slot) {
        return _slots.count(slot) > 0;
    }

    bool HasItemWithSessionId(unsigned int session_id) {
        for (auto const& slot : _slots)
            if (slot.second->SessionItemId() == session_id) 
                return true;

        return false;
    }

    bool HasItemInSlot(std::string slot) {
        if (HasSlot(slot))
            return _slots[slot] != nullptr;
        else
            return false;
    }

    bool EquipItem(std::string slot, Item* item_to_add)
    {

        if (ValidSlotForItem(slot, item_to_add)) {
            _slots[slot] = item_to_add;
            return true;
        }
        else
            return false;
    }

    Item* UnequipItem(std::string slot)
    {
        // If slot exists and has an item in it.
        if (_slots.count(slot) && _slots[slot] != nullptr) {
            Item* returnItem = _slots[slot];
            _slots[slot] = nullptr;
            return returnItem;
        }
        else
            return nullptr;
    }

    List<Stat> CountStats() {
        std::map<std::string, double> countedStats;
        List<Stat> returnStats;
        for (auto const& slot : _slots) {

            if (slot.second != nullptr) {
                for (auto stat : slot.second->Stats()) {
                    if (!countedStats.count(stat.Name()))
                        countedStats.insert(std::pair<std::string, double>(stat.Name(), stat.Value()));
                    else
                        countedStats[stat.Name()] += stat.Value();
                } // end for
            } // end if
        } // end for

        return returnStats;
    }

    void PrintItems() {
        for (auto const& slot : _slots) {
            std::cout << slot.first << ": ";
            if (slot.second != nullptr)
                std::cout << slot.second->Name();
            std::cout << std::endl;
        }
    }

    std::map<std::string, Item*> Slots() const { return _slots; }

    bool ValidSlotForItem(std::string slot, Item* item_to_add) {

        // if no such slot exists.
        if (_slots.count(slot) < 1)
            return false;

        // if the item slot is a specific slot, for example "righthand" or "leftwrist".
        // or, more commonly, "legs" or "waist".
        if (slot == item_to_add->Slot())
            return true;

        // Check every specific slot for the slot of the item.
        for (const auto& specificSlot : _slotMappings[item_to_add->Slot()]) {

            if (specificSlot == slot) {
                // The slot we want to equip exists for the items overarching slot.
                // For example, we want to equip in the "righthand" and the item has slot "hand"
                // We check _slotMappings.Map()["hand"] if "righthand" exists in it.
                return true;
            }
        }

        return false;
    }

private:
    std::map<std::string, Item*> _slots;

    // "hand" items can be equipped in left or right hand.
    // "ring" items can be equipped in ring1, ring2, ring3, or ring4.
    // etc.
    std::map<std::string, std::unordered_set<std::string>> _slotMappings;

};
