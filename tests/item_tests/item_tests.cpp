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

			Item excalibur = itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);

			Assert::AreEqual(name, excalibur.Name());
			Assert::AreEqual(slot, excalibur.Slot());
		} // End TEST_METHOD

		

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

			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);

			for (auto const& item : itemManager.GetSessionItems()->Items()) {
				// Try to equip, should return false
				Assert::AreEqual(false, itemManager.EquipBySessionId(item.first, item.second.Slot()));
			}
		}

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

			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);

			// Check that each item in the session has a unique session id.
			// and that the keys and values are paired correctly.
			unsigned int lastID = 696969; // impossible to generate in this small test
			for (const auto item : itemManager.GetSessionItems()->Items()) {
				Assert::AreNotEqual(lastID, item.second.SessionItemId());
				Assert::AreEqual(item.first, item.second.SessionItemId());
				lastID = item.second.SessionItemId();
			}

			// Add items in session to inventory.
			for (auto item : itemManager.GetSessionItems()->Items()) {
				itemManager.AddItemToInventoryBySessionId(item.second.SessionItemId());
				Assert::AreEqual(true, itemManager.GetInventory()->HasItemWithSessionId(item.second.SessionItemId()));
			}
			
		} // End TEST_METHOD

		TEST_METHOD(Should_HaveEqualSessionIDKeyAndValueSessionID_InSessionItems) {

			ItemManager itemManager = ItemManager();

			std::string name = "Excalibur";
			std::string slot = "hand";
			std::string possible_stat_1 = "strength";
			std::string possible_stat_2 = "vitality";

			auto possibleStatsExcalibur = List<PossibleStat>();
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_1, 500, 750, 1));
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_2, 500, 750, 1));
			ItemBase possibleExcalibur = ItemBase(name, possibleStatsExcalibur, slot);

			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);

			// Check that the keys and values are paired correctly.
			for (const auto item : itemManager.GetSessionItems()->Items())
				Assert::AreEqual(item.first, item.second.SessionItemId());

		} // End TEST_METHOD

		TEST_METHOD(Should_HaveItemInInventory_WhenAddingItems) {

			ItemManager itemManager = ItemManager();

			std::string name = "Excalibur";
			std::string slot = "hand";
			std::string possible_stat_1 = "strength";
			std::string possible_stat_2 = "vitality";

			auto possibleStatsExcalibur = List<PossibleStat>();
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_1, 500, 750, 1));
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_2, 500, 750, 1));
			ItemBase possibleExcalibur = ItemBase(name, possibleStatsExcalibur, slot);

			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);

			// Add items in session to inventory.
			for (auto item : itemManager.GetSessionItems()->Items()) {
				itemManager.AddItemToInventoryBySessionId(item.second.SessionItemId());
				Assert::AreEqual(true, itemManager.GetInventory()->HasItemWithSessionId(item.second.SessionItemId()));
			}

		} // End TEST_METHOD

		TEST_METHOD(Should_HaveItemInInventory_AfterAddingItems) {

			ItemManager itemManager = ItemManager();

			std::string name = "Excalibur";
			std::string slot = "hand";
			std::string possible_stat_1 = "strength";
			std::string possible_stat_2 = "vitality";

			auto possibleStatsExcalibur = List<PossibleStat>();
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_1, 500, 750, 1));
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_2, 500, 750, 1));
			ItemBase possibleExcalibur = ItemBase(name, possibleStatsExcalibur, slot);

			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);

			// Add items in session to inventory.
			for (auto item : itemManager.GetSessionItems()->Items())
				itemManager.AddItemToInventoryBySessionId(item.second.SessionItemId());

			// Check if item is in inventory.
			for (auto item : itemManager.GetSessionItems()->Items())
				Assert::AreEqual(true, itemManager.GetInventory()->HasItemWithSessionId(item.second.SessionItemId()));

		} // End TEST_METHOD
		
		TEST_METHOD(Should_HaveEqualSessionIDKeyAndValueSessionID_WhenAddingItemsToInventory) {

			ItemManager itemManager = ItemManager();

			std::string name = "Excalibur";
			std::string slot = "hand";
			std::string possible_stat_1 = "strength";
			std::string possible_stat_2 = "vitality";

			auto possibleStatsExcalibur = List<PossibleStat>();
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_1, 500, 750, 1));
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_2, 500, 750, 1));
			ItemBase possibleExcalibur = ItemBase(name, possibleStatsExcalibur, slot);

			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);
			itemManager.GetGenerator()->GenerateItemWithBase(possibleExcalibur);


			// Add items in session to inventory.
			for (auto& item : itemManager.GetSessionItems()->Items()) {
				itemManager.AddItemToInventoryBySessionId(item.second.SessionItemId());
				Assert::AreEqual(true, itemManager.GetInventory()->HasItemWithSessionId(item.second.SessionItemId()));
			}

			// Check if the mapping is correct. pair with 1 as first should have second.SessionItemId() == 1.
			for (auto item : itemManager.GetInventory()->Items()) {
				unsigned int mapID = item.first;
				unsigned int itemID = item.second->SessionItemId();
				Assert::AreEqual(mapID, itemID);
			}
			
			
		} // End TEST_METHOD

	};
}
