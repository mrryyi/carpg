#include "preincludes.h"


int main()
{
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

	itemManager.AddItemToInventoryBySessionId(excalibur.SessionItemId());
	itemManager.AddItemToInventoryBySessionId(excalibur2.SessionItemId());
	itemManager.AddItemToInventoryBySessionId(thunderfury.SessionItemId());

	Printer::PrintInventory(itemManager.GetInventory());

	itemManager.EquipBySessionId(excalibur.SessionItemId(), "righthand");
	itemManager.EquipBySessionId(excalibur2.SessionItemId(), "lefthand");

	Printer::PrintEquipment(itemManager.GetEquipment());
	Printer::PrintInventory(itemManager.GetInventory());
	Printer::PrintEquipmentStats(itemManager.GetEquipment());

}
/*

int main() {
	ItemManager itemManager = ItemManager();

	std::string name = "Excalibur";
	std::string slot = "hand";
	std::string possible_stat_1 = "strength";
	std::string possible_stat_2 = "vitality";

	auto possibleStatsExcalibur = List<PossibleStat>();
	possibleStatsExcalibur.push_back(PossibleStat(possible_stat_1, 500, 750, 1));
	possibleStatsExcalibur.push_back(PossibleStat(possible_stat_2, 500, 750, 1));
	ItemBase possibleExcalibur = ItemBase(name, possibleStatsExcalibur, slot);

	itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
	itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
	itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
	itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
	itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);


	// Add items in session to inventory.
	for (auto& item : itemManager.GetSessionItems()->Items()) {
		itemManager.AddItemToInventoryBySessionId(item.second.SessionItemId());
		unsigned int mapID = item.first;
		unsigned int itemID = item.second.SessionItemId();
		std::cout << "ID in map: " << mapID  << ", ID in item: " << itemID <<  std::endl;

	}

	for (auto& item : itemManager.GetInventory()->Items()) {

		unsigned int mapID = item.first;
		//unsigned int itemID = item.second->SessionItemId();
		
		std::cout << "ID in map: " << mapID  << ", ID in item: " << item.second->SessionItemId() << ", item pointer: " << item.second <<  std::endl;
	}

	//Printer::PrintInventory(itemManager.GetInventory());
}

*/