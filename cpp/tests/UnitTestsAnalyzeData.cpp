#include "pch.h"
#include "CppUnitTest.h"

#include <string>
#include "../src/analyzer.h"
#include "../src/analyzer.cpp"
#include "../src/RNG.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		TEST_METHOD(TestAnalyzeGetAffinity)
		{
			Configs configs{ 1.0, "input.txt", "output.txt", false };
			std::unique_ptr<RNG> default_rng = std::make_unique<DefaultRNG>();
			std::unique_ptr<Analyzer> analyzer = std::make_unique<Analyzer>(std::move(default_rng), configs);

			auto row = Row { AgentBreed::Breed_C, 132802001.0, 66, 3, 250, 25.3, 16.6, 5.1, false, 4 };
			double affinity = analyzer->GetAffinity(row);
			double expected_affinity = 45.6602;
			Assert::AreEqual(affinity, expected_affinity, 0.0001);
		}

		TEST_METHOD(TestAnalyzeConditions)
		{
			Configs configs{ 2.0, "input.txt", "output.txt", false };
			std::unique_ptr<RNG> default_rng = std::make_unique<DefaultRNG>();
			std::unique_ptr<Analyzer> analyzer = std::make_unique<Analyzer>(std::move(default_rng), configs);
			auto row = Row{ AgentBreed::Breed_C, 132802001.0, 66, 3, 250, 12.3, 16.6, 5.1, false, 4 };
			bool is_c_condition_true = analyzer->IsCConditionTrue(row);
			bool is_nc_condition_true = analyzer->IsNCConditionTrue(row);
			Assert::IsFalse(is_c_condition_true);
			Assert::IsTrue(is_nc_condition_true);
		}
		TEST_METHOD(TestAnalyzeAnalyzeRows)
		{
			Configs configs{ 1.0, "input.txt", "output.txt", false};
			std::unique_ptr<RNG> default_rng = std::make_unique<DefaultRNG>();
			std::unique_ptr<Analyzer> analyzer = std::make_unique<Analyzer>(std::move(default_rng), configs);

			auto row1 = Row{AgentBreed::Breed_C, 132802001.0, 66, 3, 250, 25.3, 16.6, 5.1, false, 4};
			auto row2 = Row{AgentBreed::Breed_C, 132802002.0, 66, 3, 250, 12.3, 16.6, 5.1, false, 4};
			analyzer->Analyze(row1);
			analyzer->Analyze(row2);
			auto results = analyzer->GetResults();
			Assert::AreEqual(results.size(), size_t{ 1 });
			Assert::AreEqual(results[0].breed_c_ids.size(), size_t{ 1 });
			Assert::AreEqual(results[0].breed_nc_ids.size(), size_t{ 1 });
			Assert::AreEqual(results[0].breed_c_lost_ids.size(), size_t{ 1 });
			Assert::AreEqual(results[0].breed_c_gained_ids.size(), size_t{ 0 });
			Assert::AreEqual(results[0].breed_c_regained_ids.size(), size_t{ 0 });
		}
	};
}
