#include "preincludes.h"

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
