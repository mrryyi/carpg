#include "preincludes.h"
int main() {

	// Has session_items array.
	ItemManager item_manager = ItemManager();

	std::string name = "Excalibur";
	std::string slot = "hand";
	std::string possible_stat_1 = "strength";
	std::string possible_stat_2 = "vitality";

	auto possibleStatsExcalibur = List<PossibleStat>();
	possibleStatsExcalibur.push_back(PossibleStat(possible_stat_1, 500, 750, 1));
	possibleStatsExcalibur.push_back(PossibleStat(possible_stat_2, 500, 750, 1));
	ItemBase possibleExcalibur = ItemBase(name, possibleStatsExcalibur, slot);

	// Create an item, we have the id of the item
	unsigned int item_session_id = item_manager.generate_item_with_base(possibleExcalibur);

	if (item_manager.item_exists(item_session_id))
		std::cout << "item exists." << std::endl;


	// Create an inventory, we have the id of the inventory.
	unsigned int inventory_session_id = item_manager.new_item_container(64);
	item_manager.move_item_to_container(item_session_id, inventory_session_id);

	if (item_manager.container_exists(inventory_session_id))
		std::cout << "inventory exists." << std::endl;

	// Get the items in inventory and print them.
}