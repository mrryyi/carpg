#pragma once
#include <vector>
#include <unordered_set>

// Slots are defined by the index in the vector.
// A 0 value in the _items vector represents a non-existing item session id.
class ItemContainer {
public:
	ItemContainer(unsigned int id, unsigned int size) {
		_id = id;
		_items = std::vector<unsigned int>(size);
	}

	bool is_full() {
		return _amount_of_items == _size - 1;
	}

	bool contains(unsigned int session_item_id) {
		for (int i = 0; i < _size; i++ ) {
			if (_items[i] == session_item_id)
				return true;
		}

		return false;
	}

	// returns true if successful
	bool add_item_first_available_slot(unsigned int session_item_id) {

		for (int i = 0; i < _size; i++) {
			if (_items[i] == 0) {
				_items[i] = session_item_id;
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
			if (_items[i] == session_item_id) {
				remove_item(i);
				return true;
			}
		}

		return false;
	}

	std::vector<unsigned int> get_items() const { return _items; };
	unsigned int get_size() const { return _size; };
	unsigned int get_current_amount_of_items() const { return _amount_of_items; };

private:

	void remove_item(unsigned int slot) {
		_items[slot] = 0;
		_amount_of_items -= 1;
	}

	bool slot_is_taken(unsigned int slot) {

		if (slot >= _size)
			return true;

		return _items[slot] != 0;
	}

	std::vector<unsigned int> _items;

	unsigned int _id;
	unsigned int _size;
	unsigned int _amount_of_items;
};