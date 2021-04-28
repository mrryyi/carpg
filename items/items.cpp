#include "preincludes.h"

int main() {

	srand(time(NULL));

	ItemManager itemManager = ItemManager();

	std::string name = "Excalibur";
	std::string slot = "hand";
	std::string possible_stat_1 = "strength";
	std::string possible_stat_2 = "vitality";

	auto possibleStatsExcalibur = List<StatPossibility>();
	possibleStatsExcalibur.push_back(StatPossibility(possible_stat_1, 500, 750, 1));
	possibleStatsExcalibur.push_back(StatPossibility(possible_stat_2, 500, 750, 1));
	ItemBase possibleExcalibur = ItemBase(name, possibleStatsExcalibur, slot);

	auto inventory_id = itemManager.new_item_container(24);
	auto stash_id = itemManager.new_item_container(24);

	std::cout << "inventory_id: " << inventory_id << std::endl;
	std::cout << "stash_id: " << stash_id << std::endl;

	unsigned int item_id;
	for (int i = 0; i < 10; i++) {
		item_id = itemManager.generate_item_with_base(possibleExcalibur);
		itemManager.move_item_to_container(inventory_id, item_id);
	}

	for (int i = 0; i < 10; i++) {
		item_id = itemManager.generate_random_item();
		itemManager.move_item_to_container(inventory_id, item_id);
	}

	print_item_container(itemManager.get_container(inventory_id));

	auto items = itemManager.get_items_in_container(inventory_id);
	for (int i = 0; i < items.size(); i++)
		item_id = itemManager.move_item_to_container(stash_id, items[i]->SessionItemId());

	print_item_container(itemManager.get_container(inventory_id));
	print_item_container(itemManager.get_container(stash_id));
	print_items_in_container(itemManager.get_container(stash_id));
}

/*
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

	if (item_manager.container_exists(inventory_session_id))
		std::cout << "inventory exists." << std::endl;

	bool item_moved = item_manager.move_item_to_container(inventory_session_id, item_session_id);
	if (item_moved) {
		std::cout << "item moved" << std::endl;
	}

	// Get the items in inventory and print them.
	Item* item = item_manager.get_one_item(item_session_id);
	std::cout << item->Name() << ": hello uwu i wish you wuwdnt wake me uwp :(" << std::endl;

	std::vector<Item*> items_in_inventory;
	item_manager.get_items_in_container_whack(inventory_session_id, items_in_inventory);

	if (items_in_inventory.size() != 0) {
		for (auto& item : items_in_inventory) {
			std::cout << "Name: " << item->Name() << std::endl;
		}
	}

	unsigned int stash_session_id = item_manager.new_item_container(64);
	unsigned int item_id;
}
*/