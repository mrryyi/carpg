#pragma once
#include "preincludes.h"

void print_item_container(ItemContainer* item_container) {
	std::vector<Item*> items = item_container->get_container_with_empty_slots();

	std::cout << "Item container id: " << item_container->get_id() << std::endl;
	for (int i = 0; i < items.size(); i++) {
		std::cout << "Slot " << i << ": ";
		if (items[i] != nullptr)
			std::cout << items[i]->Name() << ", session id = " << items[i]->SessionItemId();
		std::cout << std::endl;
	}
}

void print_items_in_container(ItemContainer* item_container) {
	std::vector<Item*> items = item_container->get_only_items();

	std::cout << "Item container id: " << item_container->get_id() << std::endl;
	for (int i = 0; i < items.size(); i++) {
		
		std::cout << "Container Slot " << i << ":" << std::endl;
		
		if (items[i] != nullptr) {
			std::cout << "Name: " << items[i]->Name() << std::endl;
			std::cout << "Equip slot:" << items[i]->Slot() << std::endl;
			std::cout << "Session id = " << items[i]->SessionItemId() << std::endl;
			for (auto& stat : items[i]->Stats()) {
				std::cout << "[" + stat.Name() + "]: " << stat.Value() << std::endl;
			}
		}

		std::cout << std::endl;
	}
}