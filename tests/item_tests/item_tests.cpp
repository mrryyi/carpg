#include "pch.h"
#include "CppUnitTest.h"
#include "preincludes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/*
https://docs.microsoft.com/en-us/visualstudio/test/writing-unit-tests-for-c-cpp?view=vs-2019
*/
namespace itemtests
{
	TEST_CLASS(itemtests)
	{
	public:
		
		TEST_METHOD(ItemGenerationTest) {

			ItemManager itemManager = ItemManager();

			std::string name = "Excalibur";
			std::string slot = "hand";
			std::string possible_stat_1 = "strength";
			std::string possible_stat_2 = "vitality";

			auto possibleStatsExcalibur = List<PossibleStat>();
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_1, 500, 750, 1));
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_2, 500, 750, 1));
			auto possibleExcalibur = ItemBase(name, possibleStatsExcalibur, slot);

			unsigned int session_item_id = itemManager.generate_item_with_base(possibleExcalibur);

			Assert::AreEqual(name, itemManager.get_one_item(session_item_id)->Name());
			Assert::AreEqual(slot, itemManager.get_one_item(session_item_id)->Slot());
		} // End TEST_METHOD

		
		/*
		TODO: IMPLEMENT EQUIPMENT AGAIN
		TEST_METHOD(Should_NotEquipItem_WhenItemNotInInventory) {
			ItemManager itemManager = ItemManager();

			std::string name = "Excalibur";
			std::string slot = "hand";
			std::string possible_stat_1 = "strength";
			std::string possible_stat_2 = "vitality";

			auto possibleStatsExcalibur = List<PossibleStat>();
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_1, 500, 750, 1));
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_2, 500, 750, 1));
			ItemBase possibleExcalibur = ItemBase(name, possibleStatsExcalibur, slot);

			unsigned int inventory_id = itemManager.new_item_container(64);

			for (int i = 0; i < 10; i++) {
				unsigned int item_id = itemManager.generate_item_with_base(possibleExcalibur);
				itemManager.move_item_to_container(inventory_id, item_id);
			}

			for (auto const& item : itemManager.GetSessionItems()->Items()) {
				// Try to equip, should return false
				Assert::AreEqual(false, itemManager.EquipBySessionId(item.first, item.second.Slot()));
			}
		}

		TEST_METHOD(Should_EquipItem_WhenItemInInventory) {
			ItemManager itemManager = ItemManager();

			std::string name = "Excalibur";
			std::string slot = "hand";
			std::string possible_stat_1 = "strength";
			std::string possible_stat_2 = "vitality";

			auto possibleStatsExcalibur = List<PossibleStat>();
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_1, 500, 750, 1));
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_2, 500, 750, 1));
			ItemBase possibleExcalibur = ItemBase(name, possibleStatsExcalibur, slot);

			Item* excalibur = itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);

			itemManager.AddItemToInventoryBySessionId(excalibur->SessionItemId());
			// Try to equip, should return true
			Assert::AreEqual(true, itemManager.EquipBySessionId(excalibur->SessionItemId(), "righthand"));

		}*/

		TEST_METHOD(Should_HaveUniqueSessionId_WhenGeneratingItems) {

			ItemManager itemManager = ItemManager();

			std::string name = "Excalibur";
			std::string slot = "hand";
			std::string possible_stat_1 = "strength";
			std::string possible_stat_2 = "vitality";

			auto possibleStatsExcalibur = List<PossibleStat>();
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_1, 500, 750, 1));
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_2, 500, 750, 1));
			ItemBase possibleExcalibur = ItemBase(name, possibleStatsExcalibur, slot);

			unsigned int last_id = itemManager.generate_item_with_base(possibleExcalibur);
			unsigned int session_item_id;
			unsigned int i = 0;

			for (int i = 0; i < 100; i++) {
				session_item_id = itemManager.generate_item_with_base(possibleExcalibur);
				Assert::AreNotEqual(last_id, session_item_id);
				last_id = session_item_id;
			}
			
		} // End TEST_METHOD

		TEST_METHOD(Should_HaveEqualSessionIDKeyAndValue_InSessionItems) {

			ItemManager itemManager = ItemManager();

			std::string name = "Excalibur";
			std::string slot = "hand";
			std::string possible_stat_1 = "strength";
			std::string possible_stat_2 = "vitality";

			auto possibleStatsExcalibur = List<PossibleStat>();
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_1, 500, 750, 1));
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_2, 500, 750, 1));
			ItemBase possibleExcalibur = ItemBase(name, possibleStatsExcalibur, slot);

			itemManager.generate_item_with_base(possibleExcalibur);
			itemManager.generate_item_with_base(possibleExcalibur);
			itemManager.generate_item_with_base(possibleExcalibur);
			itemManager.generate_item_with_base(possibleExcalibur);
			itemManager.generate_item_with_base(possibleExcalibur);
			itemManager.generate_item_with_base(possibleExcalibur);

			// Check that the keys and values are paired correctly.
			for (auto& item : itemManager.get_session_items())
				Assert::AreEqual(item.first, item.second->SessionItemId());

		} // End TEST_METHOD

		TEST_METHOD(Should_HaveItemsInInventory_WhenAddingItems) {

			ItemManager itemManager = ItemManager();

			std::string name = "Excalibur";
			std::string slot = "hand";
			std::string possible_stat_1 = "strength";
			std::string possible_stat_2 = "vitality";

			auto possibleStatsExcalibur = List<PossibleStat>();
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_1, 500, 750, 1));
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_2, 500, 750, 1));
			ItemBase possibleExcalibur = ItemBase(name, possibleStatsExcalibur, slot);

			auto inventory_id = itemManager.new_item_container(64);
			unsigned int item_id;
			for (int i = 0; i < 20; i++) {
				item_id = itemManager.generate_item_with_base(possibleExcalibur);
				itemManager.move_item_to_container(inventory_id, item_id);
				Assert::AreEqual(true, itemManager.container_has_item(inventory_id, item_id));
			}

		} // End TEST_METHOD 

		TEST_METHOD(Should_HaveItemsInSecondContainer_WhenMovingItems) {
			ItemManager itemManager = ItemManager();

			std::string name = "Excalibur";
			std::string slot = "hand";
			std::string possible_stat_1 = "strength";
			std::string possible_stat_2 = "vitality";

			auto possibleStatsExcalibur = List<PossibleStat>();
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_1, 500, 750, 1));
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_2, 500, 750, 1));
			ItemBase possibleExcalibur = ItemBase(name, possibleStatsExcalibur, slot);

			auto inventory_id = itemManager.new_item_container(64);
			unsigned int item_id;
			for (int i = 0; i < 20; i++) {
				item_id = itemManager.generate_item_with_base(possibleExcalibur);
				itemManager.move_item_to_container(inventory_id, item_id);
			}

			auto stash_id = itemManager.new_item_container(128);

			for (auto& item : itemManager.get_items_in_container(stash_id)) {
				item_id = itemManager.move_item_to_container(stash_id, item->SessionItemId());
				Assert::AreEqual(true, itemManager.container_has_item(stash_id, item_id));
			}

		}

	};
}
