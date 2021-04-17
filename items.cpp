#include <iostream> // for cout
#include <vector> // for vector
#include <map> // for map
#include <string> // for to_string
#include <iterator> // for back_inserter

#define List std::vector

int next_session_item_id() {
    static int nextID = 0;
    return ++nextID;
}

class Stat
{

public:
    Stat(std::string Name, double Value)
    {
        _name = Name;
        _value = Value;
    }

    std::string Name() const {
        return this->_name;
    };
    double Value () const {
        return _value;
    }
private:
    std::string _name;
    double _value;
};


// This class is to define what a certain stat on an item could be.
// Usage:
// For example, using an array of PossibleStat,
// we can generate the numbers for the resulting item.
// PossibleStat("strength", 500, 750) will be used to generate a strength stat
// with a value between 500 and 750.

class PossibleStat {

public:
    PossibleStat(std::string Name, double RangeMin, double RangeMax, double Step)
    {
        _name = Name;
        _rangeMin = RangeMin;
        _rangeMax = RangeMax;
        _step = Step;
    }

    std::string Name() { return _name; }
    double RangeMin() { return _rangeMin; }
    double RangeMax() { return _rangeMax; }
    double Step() { return _step; }

private:
    std::string _name;
    double _rangeMax;
    double _rangeMin;
    double _step;
};

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

    List<Stat> Stats() const  { return _stats; }
    std::string Name() const { return _name; }
    std::string Slot() const { return _slot; }
    int SessionItemId() const { return _sessionItemId;  }
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

    List<PossibleStat> PossibleStats () const { return _possibleStats; }
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
        // TODO: Make this cooler with a standard algorithm
        for (auto item = _items.begin(); item != _items.end(); item++) {

            if ((*item)->SessionItemId() == item_to_remove->SessionItemId()) {
                _items.erase(item);
                break; // Break or it will maybe probably break. Idk haven't checked.
            }
        }

        /*
        // Does not work for some reason.
        int session_id = item_to_remove.SessionItemId();

        auto it = std::remove_if(
            _items.begin()
            ,_items.end()
            ,[session_id](Item curr_item)->bool { return curr_item.SessionItemId() == session_id; }
            ,_items.end());
        */

    }

    List<Item*> Items () const { return _items; }
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
    }

    bool EquipItem(std::string slot, Item* item_to_add)
    {

        if (_slots.count(slot) && _slots[slot] == nullptr) // If slot exists and has no item in it.
        {
            _slots[slot] = item_to_add;
            return true;
        }
        else
            return false;
    }

    Item* UnequipItem(std::string slot)
    {
        if (_slots.count(slot) && _slots[slot] != nullptr) // If slot exists and has an item in it.
        {

            Item* returnItem = _slots[slot];
            _slots[slot] = nullptr;
            return returnItem;
        }
        else
        {
            return nullptr;
        }
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
                }
            }
        }

        for (auto const& countedStat : countedStats)
            returnStats.push_back(Stat(countedStat.first, countedStat.second));

        return List<Stat>();
    }

    std::map<std::string, Item*> Slots() const { return _slots; }

private:
    std::map<std::string, Item*> _slots;

};


namespace Generator {

    static double RandomNumberWithinRangeWithStep(double rangeMin, double rangeMax, double step)
    {

        /*
        // We are doing the times 100 thing because we don't want values like this: 0.60000000005
        rangeMin *= 100;
        rangeMax *= 100;
        step *= 100;
        var randomGenerator = new Random();

        var difference = rangeMax - rangeMin;

        var randomWithinDifference = randomGenerator.NextDouble() * difference;
        var rounded = Math.Round((randomWithinDifference / step), MidpointRounding.AwayFromZero) * step;
        var generatedNumber = (rounded + rangeMin) / 100;
        */
        double generatedNumber = 69.69;
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

    static Item GenerateItem(std::string name, List<PossibleStat> possibleStats, std::string slot)
    {
        List<Stat> generatedStats = List<Stat>();

        for (PossibleStat possibleStat : possibleStats) {
            generatedStats.push_back(GenerateStat(possibleStat));
        }

        return Item(name, generatedStats, slot);
    }

    static Item GenerateItemWithBase(ItemBase itemBase)
    {
        /*
        List<Stat> generatedStats = new List<Stat>();

        foreach (PossibleStat possibleStat in itemBase.PossibleStats)
            generatedStats.Add(GenerateStat(possibleStat));
        */

        return GenerateItem(itemBase.Name(), itemBase.PossibleStats(), itemBase.Slot());
    }

};

class StaticSlotMappings {
public:
    StaticSlotMappings() {
        _slotMappings.insert(
            {
                { "hand", List<std::string>{ "lefthand","righthand" } },
                { "ring", List<std::string> {"ring1","ring2","ring3","ring4"} },
                { "foot", List<std::string> {"leftfoot","rightfoot"} },
                { "wrist", List<std::string> { "leftwrist", "rightwrist" } }
            }
        );
    }
    std::map<std::string, List<std::string>> Map() const { return _slotMappings; }
private:
    std::map<std::string, List<std::string>> _slotMappings;
};

namespace EquipmentInventoryFace
{
    static StaticSlotMappings _slotMappings;

    // Wait, doesn't the item have a slot already?
    // Well, here's the kicker, even if the slot is "hand", we need to declare which hand. :)
    // Returns true if successful, returns false if unsuccessful.
    // Unsuccessful if the wanted slot to equip in does not match with the items slot
    static bool Equip(Inventory inventory, Equipment equipment, Item* item, std::string slot) {

        std::cout << "Trying to equip??" << std::endl;

        if (!equipment.Slots().count(slot)) {
            std::cout << "slot doesn't exist" << std::endl;

            return false;
        }
        
        if (equipment.Slots()[slot] == nullptr) {
            std::cout << slot << ": slot is nullptr" << std::endl;

            if (_slotMappings.Map().count(item->Slot())) {
                std::cout << "Slotmappings contains item slot " << std::endl;
                for (auto const& mapping : _slotMappings.Map()) {
                    std::cout << mapping.first << std::endl;
                    for (auto const& specificSlot : mapping.second) {
                        std::cout << "* " << specificSlot;
                        if (specificSlot == slot) {

                            equipment.EquipItem(slot, item);
                            inventory.RemoveItem(item);
                            std::cout << " <-- Equipping on this slot";

                            std::cout << std::endl;
                            return true;
                        }
                        std::cout << std::endl;
                    }
                }
            }
            


            for(auto specificSlot : _slotMappings.Map()[item->Slot()]) {
                std::cout << "specific slot: " << specificSlot << std::endl;
                
                if (slot == specificSlot) {
                    std::cout << ("Equipping and removing" + item->Name()) << std::endl;
                    equipment.EquipItem(slot, item);
                    inventory.RemoveItem(item);
                    return true;
                }
            }

            // This is the case if the items slot is NOT a general slot like "hand"
            // but rather a specific slot like  "righthand"

            if (slot == item->Slot()) {
                equipment.EquipItem(slot, item);
                inventory.RemoveItem(item);
                return true;
            }
        }

        return false;
    }

    static bool UnEquip(Inventory inventory, Equipment equipment, std::string slot) {
        if (equipment.Slots().count(slot) && equipment.Slots()[slot] != nullptr) // If slot exists and is not empty
        {
            Item* unequippedItem = equipment.UnequipItem(slot);
            inventory.AddItem(unequippedItem);
            return true;
        }

        return false;
    }
};

static class Printer
{
public:

    static void PrintLine(std::string str) {
        std::cout << (str) << std::endl;
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

    static void PrintInventory(Inventory inventory) {
        PrintLine("INVENTORY");
        for(auto item : inventory.Items()) {
            PrintLine(item->Name() + ':');
            for (auto stat : item->Stats())
                PrintStat(stat);
            PrintLine("");
        };

        PrintLine("-----------------------------");
    }

    static void PrintEquipment(Equipment equipment) {
        PrintLine("EQUIPMENT");
        for(auto slot : equipment.Slots())
            if (slot.second != nullptr)
                PrintLine(slot.first + ": " + slot.second->Name());

        PrintLine("-----------------------------");
    }

    static void PrintEquipmentStats(Equipment equipment) {
        auto countedStats = equipment.CountStats();

        PrintLine("EQUIPMENT STATS");
        for(auto countedStat : countedStats)
            PrintLine(countedStat.Name() + ':' + std::to_string(countedStat.Value()));
        PrintLine("-----------------------------");

    }
};

int main()
{
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

    Printer::PrintInventory(inventory);


    Equipment equipment = Equipment();

    EquipmentInventoryFace::Equip(inventory, equipment, &excalibur, "righthand");
    EquipmentInventoryFace::Equip(inventory, equipment, &excalibur2, "lefthand");
    //EquipmentInventoryFace::UnEquip(inventory, equipment, "righthand");
    //EquipmentInventoryFace::UnEquip(inventory, equipment, "lefthand");

    Printer::PrintEquipment(equipment);
    Printer::PrintInventory(inventory);
}
