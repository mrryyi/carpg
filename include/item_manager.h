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
        _item_containers = std::map<unsigned int, ItemContainer*>();
        _session_items = std::map<unsigned int, Item*>();
    }

    ~ItemManager() {
        for (auto i = _item_containers.begin(); i != _item_containers.end(); i++) 
            delete i->second;

        for (auto i = _session_items.begin(); i != _session_items.end(); i++)
            delete i->second;
    }

    unsigned int new_item_container(unsigned int size) {
        unsigned int id = next_item_container_id();
        _item_containers[id] = new ItemContainer(id, size);
        return id;
    }

    bool container_has_item(unsigned int container_id, unsigned int session_item_id) {
        if (!container_exists(container_id))
            return false;

        if (!item_exists(session_item_id))
            return false;

        return _item_containers[container_id]->contains(session_item_id);
    }

    unsigned int container_that_contains_item(unsigned int session_item_id) {
        for (auto item_container : _item_containers) {
            if (item_container.second->contains(session_item_id)) {
                return item_container.first;
            }
        }

        return 0;
    }

    ItemContainer* get_container(unsigned int item_container_id) {
        if (container_exists(item_container_id))
            return _item_containers[item_container_id];
        else
            return nullptr;
    }

    Item* get_one_item(unsigned int session_item_id) {
        return _session_items[session_item_id];
    }

    void get_items_in_container_whack(unsigned int container_id, std::vector<Item*>& found_items) {

        if (container_exists(container_id)) {
            std::vector<Item*> items_in_container;
            ItemContainer* container = _item_containers[container_id];
            found_items = container->get_only_items();
        }
    }

    std::vector<Item*> get_items_in_container(unsigned int container_id) {
        
        if (container_exists(container_id)) {
            std::vector<Item*> items_in_container;
            ItemContainer* container = _item_containers[container_id];
            return container->get_only_items();
        }
    }

    bool switch_container(unsigned int from_container, unsigned int to_container, unsigned int session_item_id) {
        debug_print("switch_container", "attempting to switch item " + _session_items[session_item_id]->Name() + " (SID=" + std::to_string(session_item_id) + ")"
                                      + " from container " + std::to_string(from_container)
                                      + " to " + std::to_string(to_container));

        if (_item_containers[from_container]->remove_item_by_item_session_id(session_item_id)) {

            debug_print("switch_container", "before adding item");

            _item_containers[to_container]->add_item_first_available_slot(get_one_item(session_item_id));

            debug_print("switch_container", "switched");
            return true;
        }
        debug_print("switch_container", "switching didn't happen");
        return false;
    }

    bool move_item_to_container(unsigned int to_item_container_id, unsigned int session_item_id) {
        
        // No such item.
        if (item_exists(session_item_id) == false)
            return false;
        
        // No such container.
        if (container_exists(to_item_container_id) == false)
            return false;

        // Container to move to is full.
        if (_item_containers[to_item_container_id]->is_full())
            return false;

        debug_print("move_item_to_container", "item exists, container exists, container isn't full.");

        unsigned int the_items_current_container = container_that_contains_item(session_item_id);

        // The item has no current container! Feel free to add without switching.
        if (the_items_current_container == 0) {
            _item_containers[to_item_container_id]->add_item_first_available_slot(_session_items[session_item_id]);
        }
        else {
            // If there is a container that contains the item, then switch between them.
            switch_container(the_items_current_container, to_item_container_id, session_item_id);
        }
        
        debug_print("move_item_to_container", "item move is successful.");

        return true;
    }

    // What is known about the item should also be its item base when we read it in.
    unsigned int create_item_from_known_item_info(std::string name, std::vector<Stat> stats, std::string slot) {
        unsigned int next_session_id = next_session_item_id();

        debug_print("create_item_from_known_item_info", "session id = " + std::to_string(next_session_id));

        _session_items[next_session_id] = new Item(name, stats, slot, next_session_id);
        return next_session_id;
    }

    unsigned int generate_item(std::string name, std::vector<PossibleStat> possibleStats, std::string slot) {
        ItemBase itemBase = ItemBase(name, possibleStats, slot);
        return generate_item_with_base(itemBase);
    }

    unsigned int generate_item_with_base(ItemBase itemBase) {

        std::vector<Stat> generatedStats = std::vector<Stat>();

        for (PossibleStat possibleStat : itemBase.PossibleStats())
            generatedStats.push_back(generate_stat(possibleStat));

        unsigned int current_session_id = next_session_item_id();

        _session_items[current_session_id] = new Item(itemBase.Name(), generatedStats, itemBase.Slot(), current_session_id);

        debug_print("generate_item_with_base", "session id = " + std::to_string(current_session_id));
        return current_session_id;
    }

    bool container_exists(unsigned int item_container_id) {
        return _item_containers.count(item_container_id) > 0;
    }

    bool item_exists(unsigned int session_item_id) {
        return _session_items.count(session_item_id) > 0;
    }

    std::map<unsigned int, Item*> get_session_items() {
        return _session_items;
    }

private:

    std::map<unsigned int, ItemContainer*> _item_containers;
    std::map<unsigned int, Item*> _session_items;
};