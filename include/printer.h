#pragma once
#include "preincludes.h"


void print_item_container(ItemContainer* item_container) {
	std::vector<Item*> items = item_container->get_container_with_empty_slots();

	std::cout << "Item container id: " << item_container->get_id() << std::endl;
	for (int i = 0; i < items.size(); i++) {
		std::cout << "Slot " << i << ": ";
		if (items[i] != nullptr)
			std::cout << items[i]->Name() << ", session id=" << items[i]->SessionItemId();
		std::cout << std::endl;
	}
}