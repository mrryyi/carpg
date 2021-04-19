#pragma once
#include "preincludes.h"

/*
This class is about every item that exists in the session.
It goes in here and never leaves.
Similar to an inventory, but not.
*/
class SessionItems
{
public:
    SessionItems() { }

    void NewItem(Item item_to_add)
    {
        _items[item_to_add.SessionItemId()] = item_to_add;
    }

    bool HasItemWithSessionId(unsigned int item_session_id) {
        return _items.count(item_session_id) > 0;
    }

    Item* GetItemBySessionId(unsigned int item_session_id) {
        return &_items[item_session_id];
    }

    std::unordered_map<unsigned int, Item> Items() const { return _items; }
private:
    std::unordered_map<unsigned int, Item> _items;

    void RemoveItem(Item item_to_remove)
    {
        _items.erase(item_to_remove.SessionItemId());
    }
};