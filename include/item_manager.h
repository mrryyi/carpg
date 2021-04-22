#pragma once
#include "preincludes.h"

/*
This class is about managing the pieces of the item puzzle.
It is supposed to be the only class you need to initialize in order to manage items.

Possible future TODOs if wanted:
Implement stash
* Equipment and inventory is not likely to only be the only item containers
* Should be able to equip items from other item containers
* Should be able to move items between item containers
** Perhaps just have a list of existing item containers, have them be of the inventory class, but call them "ExistingItemContainers", maybe.
** functionality to equip and unequip should still work if they are of the inventory class.
* T
Implement slots
*/
class ItemManager
{
public:
    ItemManager() {
        _inventory = new Inventory();
        _equipment = new Equipment();
        _sessionItems = new SessionItems();
        _generator = new Generator(_sessionItems);
    }

    ~ItemManager() {
        delete _inventory;
        delete _equipment;
        delete _sessionItems;
        delete _generator;
    }

    Generator* GetGenerator() const { return _generator; }
    Inventory* GetInventory() const { return _inventory; }
    Equipment* GetEquipment() const { return _equipment; }
    SessionItems* GetSessionItems() const { return _sessionItems; }

    bool AddItemToInventoryBySessionId(unsigned int session_id) {
        
        if (!_sessionItems->HasItemWithSessionId(session_id))
            return false;

        _inventory->AddItem(_sessionItems->GetItemBySessionId(session_id));
        return true;
    }

    bool UnEquip(std::string slot) {
        return EquipmentInventoryFace::UnEquip(_inventory, _equipment, slot);
    } 

    bool Equip(Item* item, std::string slot) {
        return EquipmentInventoryFace::Equip(_inventory, _equipment, item, slot);
    }

    bool EquipBySessionId(unsigned int item_session_id, std::string slot) {

        if (!_sessionItems->HasItemWithSessionId(item_session_id)) {
            debug_print("ItemManager::EquipBySessionId", "No session id exists, can't equip.");
            return false;
        }

        return EquipmentInventoryFace::Equip(_inventory, _equipment, _sessionItems->GetItemBySessionId(item_session_id), slot);
    }

private:

    Inventory* _inventory;
    Equipment* _equipment;
    SessionItems* _sessionItems;
    Generator* _generator;
};