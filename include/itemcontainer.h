#pragma once
#include <vector>
#include <unordered_set>

// Slots are defined by the index in the vector.
// A 0 value in the _items vector represents a non-existing item session id.
class ItemContainer {
public:
	ItemContainer(unsigned int id, unsigned int size) {
		_id = id;
		_size = size;
		_items = std::vector<Item*>(size);
		_amount_of_items = 0;
		std::fill(_items.begin(), _items.end(), nullptr);
	}

	bool is_full() {
		return _amount_of_items == _size - 1;
	}

	unsigned int get_id() {
		return _id;
	}

	bool contains(unsigned int session_item_id) {
		for (int i = 0; i < _size; i++ ) {
		    if (_items[i] != nullptr)
			    if (_items[i]->SessionItemId() == session_item_id)
				    return true;
	    }

	    return false;
	}

	// returns true if successful
	bool add_item_first_available_slot(Item* item) {
		for (int i = 0; i < _size; i++) {
			if (_items[i] == nullptr) {
				std::cout << "Adding to slot: " << i << std::endl;
				_items[i] = item;
				_amount_of_items += 1;
				return true;
			}
		}

        return false;
	}

	// returns true if successful
	bool remove_item_by_slot(unsigned int slot) {
		
		// if slot is not even in the inventory, we do not remove an item.
		if (slot >= _size)
			return false;

		// If slot is not taken by any item, no item was removed.
		if (!slot_is_taken(slot))
			return false;

		remove_item(slot);
		return true;
	}

	// returns true if successful
	bool remove_item_by_item_session_id(unsigned int session_item_id) {

		for (int i = 0; i < _size; i++) {
			if (_items[i] != nullptr) {
				if (_items[i]->SessionItemId() == session_item_id) {
					remove_item(i);
					return true;
				}
			}
		}

		return false;
	}

	std::vector<Item*> get_container_with_empty_slots() { return _items; };
	std::vector<Item*> get_only_items() {

		std::vector<Item*> items_in_container(_amount_of_items);
		items_in_container = _items;
		
		items_in_container.erase(
							  std::remove_if(items_in_container.begin()
									        ,items_in_container.end()
								            ,[](const Item* item) {return item == nullptr; })
			                  ,items_in_container.end());
		return items_in_container;
	};

	unsigned int get_size() const { return _size; };
	unsigned int get_current_amount_of_items() const { return _amount_of_items; };

private:

	void remove_item(unsigned int slot) {
		_items[slot] = nullptr;
		_amount_of_items -= 1;
	}

	bool slot_is_taken(unsigned int slot) {

		if (slot >= _size)
			return true;

		return _items[slot] != 0;
	}

	std::vector<Item*> _items;

	unsigned int _id;
	unsigned int _size;
	unsigned int _amount_of_items;
};