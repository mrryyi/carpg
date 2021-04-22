#pragma once
#include "preincludes.h"

/*
Possible future TODOs:
If we want different inventories, we kinda want to be able to separate them by id or name.
If we want to separate Inventory and other Item Containers, we could rename this class ItemContainer
and have subclasses Inventory, and maybe Stash, that inherit from ItemContainer, if they will have different implementations.
*/
class Inventory
{
public:
    Inventory()
    {
        _items = std::unordered_map<unsigned int, Item*>();
    }

    void AddItem(Item* item_to_add)
    {
        debug_print("Inventory::AddItem", "Added item with session ID: " + std::to_string(item_to_add->SessionItemId()));
        _items[item_to_add->SessionItemId()] = item_to_add;
    }

    void RemoveItem(Item* item_to_remove)
    {
        _items.erase(item_to_remove->SessionItemId());
    }

    bool HasItemWithSessionId(unsigned int item_session_id) {
        return _items.count(item_session_id) > 0;
    }

    Item* GetItemBySessionId(unsigned int item_session_id) {
        return _items[item_session_id];
    }

    std::unordered_map<unsigned int, Item*> Items() const { return _items; }
private:
    std::unordered_map<unsigned int, Item*>  _items;

};