#pragma once
#include "preincludes.h"

// Interface between equipment and inventory.
namespace EquipmentInventoryFace
{
    bool UnEquip(Inventory* inventory, Equipment* equipment, std::string slot) {

        if (!equipment->HasSlot(slot)) {
            debug_print("EquipmentInventoryFace:UnEquip", "UnEquip NOT successful, slot " + slot + " doesn't exist.");
            return false;
        }
        if (equipment->Slots()[slot] == nullptr) {
            debug_print("EquipmentInventoryFace:UnEquip", "UnEquip NOT successful, slot " + slot + " already empty.");
            return false;
        }

        Item* unequippedItem = equipment->UnequipItem(slot);
        if (unequippedItem != nullptr) {
            inventory->AddItem(unequippedItem);
            debug_print("EquipmentInventoryFace:UnEquip", "UnEquip of slot " + slot + " successful, " +
                "item " + unequippedItem->Name() + " now in inventory.");
            return true;
        }

        debug_print("EquipmentInventoryFace:UnEquip", "UnEquip of slot " + slot + " NOT successful, reason unknown.");
        return false;
    }

    bool Equip(Inventory* inventory, Equipment* equipment, Item* item, std::string slot) {

        if (inventory->HasItemWithSessionId(item->SessionItemId())) {
            debug_print("EquipmentInventoryFace:Equip", "Equip of item " + item->Name() + " NOT successful, inventory has no such item.");
            return false;
        }

        if (!equipment->HasSlot(slot)) {
            debug_print("EquipmentInventoryFace:Equip", "Equip of item " + item->Name() + " NOT successful, equipment has no such slot: " + slot);
            return false;
        }

        if (equipment->ValidSlotForItem(slot, item) && equipment->HasItemInSlot(slot)) {
            printf("GOT HERE\n");
            debug_print("EquipmentInventoryFace:Equip", "Item already in slot, SWITCHING ITEMS, unequipping " + equipment->Slots()[slot]->Name() + " first.");
            UnEquip(inventory, equipment, slot);

            debug_print("EquipmentInventoryFace:Equip", "Equipping item " + item->Name() + " finally, recursively.");

            // We are calling this function recursively, because now,
            // the slot in the equipment has to be a nullptr because we unequipped it.
            Equip(inventory, equipment, item, slot);

            return true;
        }

        // If equipping was successful, remove from inventory.
        if (equipment->EquipItem(slot, item)) {
            inventory->RemoveItem(item);
            debug_print("EquipmentInventoryFace:Equip", "Equip of item " + item->Name() + " in slot " + slot + " successful");
            return true;
        }

        debug_print("EquipmentInventoryFace:Equip", "Equip of item " + item->Name() + " in slot " + slot + " NOT successful, reason unknown");
        return false;
    }

};