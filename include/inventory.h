#pragma once
#include "preincludes.h"

class Inventory
{
public:
    Inventory()
    {
        _items = std::unordered_map<unsigned int, Item*>();
    }

    void AddItem(Item* item_to_add)
    {
        //_items.push_back(item_to_add);
        //_items.insert(std::pair<unsigned int, Item*>(item_to_add->SessionItemId(), item_to_add));
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