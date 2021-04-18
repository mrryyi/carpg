#include <iostream> // for cout
#include <vector> // for vector
#include <map> // for map
#include <string> // for to_string
#include <iterator> // for back_inserter
#include <stdlib.h> // srand, rand
#include <time.h> // time
#include <unordered_set> // unordered_set

#include "stat.h"

#define List std::vector
#define __DEBUGMODE__

void debug_print(std::string origin, std::string message) {
#ifdef __DEBUGMODE__
    std::cout << "[DEBUG] ORIGIN: " << origin << ", " << message << std::endl;
#endif
}

int next_session_item_id() {
    static int nextID = 0;
    return ++nextID;
}


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

class Inventory
{
public:
    Inventory()
    {
        _items = List<Item*>();
    }

    void AddItem(Item* item_to_add)
    {
        _items.push_back(item_to_add);
    }

    void RemoveItem(Item* item_to_remove)
    {
        _items.erase(std::remove(_items.begin(), _items.end(), item_to_remove), _items.end());
    }

    List<Item*> Items() const { return _items; }
private:
    List<Item*> _items;

};

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

        for (auto const& countedStat : countedStats) {
            std::cout << countedStat.first << ": " << countedStat.second << std::endl;
            returnStats.push_back(Stat(countedStat.first, countedStat.second));
        }

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

        // if the item slot is a specific slot, for example "righthand" or "leftwrist"
        if (slot == item_to_add->Slot()) {
            return true;
        }

        // Check every slot possible for the overarching slot.
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

        int difference = int( rangeMax - rangeMin );
        int randomWithinDifference = rand() % difference;
        double rounded = std::round((double) randomWithinDifference / step) * step;

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

// Interface between equipment and inventory.
namespace EquipmentInventoryFace
{

    static bool UnEquip(Inventory* inventory, Equipment* equipment, std::string slot) {

        if (!equipment->HasSlot(slot)) {
            debug_print("EquipmentInventoryFace:UnEquip", "UnEquip NOT successful, slot " + slot + " doesn't exist.");
            return false;
        }
        if (equipment->Slots()[slot] == nullptr) {
            debug_print("EquipmentInventoryFace:UnEquip", "UnEquip NOT successful, slot " + slot + " already empty.");
            return false;
        }

        Item* unequippedItem = equipment->UnequipItem(slot);
        if (unequippedItem != nullptr) {
            inventory->AddItem(unequippedItem);
            debug_print("EquipmentInventoryFace:UnEquip", "UnEquip of slot " + slot + " successful, " + 
                        "item " + unequippedItem->Name() + " now in inventory.");
            return true;
        }

        debug_print("EquipmentInventoryFace:UnEquip", "UnEquip of slot " + slot + " NOT successful, reason unknown.");
        return false;
    }

    static bool Equip(Inventory* inventory, Equipment* equipment, Item* item, std::string slot) {
        
        if (!equipment->HasSlot(slot)) {
            debug_print("EquipmentInventoryFace:Equip", "Equip of item " + item->Name() + " NOT successful, equipment has no such slot: " + slot);
            return false;
        }
         
        if (equipment->ValidSlotForItem(slot, item) && equipment->HasItemInSlot(slot)) {
            printf("GOT HERE\n");
            debug_print("EquipmentInventoryFace:Equip", "Item already in slot, SWITCHING ITEMS, unequipping " + equipment->Slots()[slot]->Name() + " first.");
            UnEquip(inventory, equipment, slot);

            debug_print("EquipmentInventoryFace:Equip", "Equipping item " + item->Name() + " finally, recursively.");

            // We are calling this function recursively, because now,
            // the slot in the equipment has to be a nullptr because we unequipped it.
            Equip(inventory, equipment, item, slot);

            return true;
        }

        // If equipping was successful, remove from inventory.
        if (equipment->EquipItem(slot, item)) {
            inventory->RemoveItem(item);
            debug_print("EquipmentInventoryFace:Equip", "Equip of item " + item->Name() + " in slot " + slot + " successful");
            return true;
        }

        debug_print("EquipmentInventoryFace:Equip", "Equip of item " + item->Name() + " in slot " + slot + " NOT successful, reason unknown");
        return false;
    }

};

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

int main()
{
    srand(time(NULL));
    std::cout << "Hello World!\n";
    auto possibleStatsExcalibur = List<PossibleStat>();
    possibleStatsExcalibur.push_back(PossibleStat("strength", 500, 750, 1));
    possibleStatsExcalibur.push_back(PossibleStat("vitality", 500, 750, 1));
    auto possibleExcalibur = ItemBase("Excalibur", possibleStatsExcalibur, "hand");


    auto possibleStatsThunderfury = List<PossibleStat>();
    possibleStatsThunderfury.push_back(PossibleStat("agility", 500, 750, 1));
    possibleStatsThunderfury.push_back(PossibleStat("critchance", 5, 8, 0.5));
    auto possibleThunderfury = ItemBase("Thunderfury, blessed blade of the windseeker", possibleStatsThunderfury, "hand");


    Item excalibur = Generator::GenerateItemWithBase(possibleExcalibur);
    Item excalibur2 = Generator::GenerateItemWithBase(possibleExcalibur);
    Item thunderfury = Generator::GenerateItemWithBase(possibleThunderfury);

    Inventory inventory = Inventory();
    inventory.AddItem(&excalibur);
    inventory.AddItem(&excalibur2);
    inventory.AddItem(&thunderfury);

    Printer::PrintInventory(&inventory);

    Equipment equipment = Equipment();

    EquipmentInventoryFace::Equip(&inventory, &equipment, &excalibur, "righthand");
    EquipmentInventoryFace::Equip(&inventory, &equipment, &excalibur2, "lefthand");
    EquipmentInventoryFace::Equip(&inventory, &equipment, &thunderfury, "righthand");
    //EquipmentInventoryFace::UnEquip(&inventory, &equipment, "righthand");
    //EquipmentInventoryFace::UnEquip(&inventory, &equipment, "lefthand");

    Printer::PrintEquipment(&equipment);
    Printer::PrintInventory(&inventory);
    Printer::PrintEquipmentStats(&equipment);
    //equipment.PrintItems();
}
