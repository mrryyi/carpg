#include "preincludes.h"

int main()
{
    srand(time(NULL));
    auto possibleStatsExcalibur = List<PossibleStat>();
    possibleStatsExcalibur.push_back(PossibleStat("strength", 500, 750, 1));
    possibleStatsExcalibur.push_back(PossibleStat("vitality", 500, 750, 1));
    auto possibleExcalibur = ItemBase("Excalibur", possibleStatsExcalibur, "hand");

    auto possibleStatsThunderfury = List<PossibleStat>();
    possibleStatsThunderfury.push_back(PossibleStat("agility", 500, 750, 1));
    possibleStatsThunderfury.push_back(PossibleStat("critchance", 5, 8, 0.5));
    auto possibleThunderfury = ItemBase("Thunderfury, blessed blade of the windseeker", possibleStatsThunderfury, "hand");

    ItemManager itemManager = ItemManager();

    Item excalibur = itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
    Item excalibur2 = itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
    Item thunderfury = itemManager.GetGenerator()->GenerateItemWithBase(possibleThunderfury);

    itemManager.GetInventory()->AddItem(&excalibur);
    itemManager.GetInventory()->AddItem(&excalibur2);
    itemManager.GetInventory()->AddItem(&thunderfury);

    Printer::PrintInventory(itemManager.GetInventory());

    itemManager.EquipBySessionId(excalibur.SessionItemId(), "righthand");
    itemManager.EquipBySessionId(excalibur2.SessionItemId(), "lefthand");

    Printer::PrintEquipment(itemManager.GetEquipment());
    Printer::PrintInventory(itemManager.GetInventory());
    Printer::PrintEquipmentStats(itemManager.GetEquipment());

}
