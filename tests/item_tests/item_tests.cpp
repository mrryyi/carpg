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

		TEST_METHOD(ItemGenerationTest)
		{

			std::string name = "Excalibur";
			std::string slot = "hand";
			std::string possible_stat_1 = "strength";
			std::string possible_stat_2 = "vitality";

			auto possibleStatsExcalibur = List<PossibleStat>();
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_1, 500, 750, 1));
			possibleStatsExcalibur.push_back(PossibleStat(possible_stat_2, 500, 750, 1));
			auto possibleExcalibur = ItemBase(name, possibleStatsExcalibur, slot);

			Item excalibur = Generator::GenerateItemWithBase(possibleExcalibur);

			Assert::AreEqual(name, excalibur.Name());
			Assert::AreEqual(slot, excalibur.Slot());
		}
	};
}
