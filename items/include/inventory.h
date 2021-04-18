#pragma once
#include "preincludes.h"

class Inventory
{
public:
    Inventory()
    {
        _items = List<Item*>();
    }

    void AddItem(Item* item_to_add)
    {
        _items.push_back(item_to_add);
    }

    void RemoveItem(Item* item_to_remove)
    {
        _items.erase(std::remove(_items.begin(), _items.end(), item_to_remove), _items.end());
    }

    List<Item*> Items() const { return _items; }
private:
    List<Item*> _items;

};