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
			double expected_affinity = 25.2602;
			Assert::AreEqual(affinity, expected_affinity);
		}

		TEST_METHOD(TestAnalyzeOneRow)
		{
			Configs configs{ 1.0, "input.txt", "output.txt", false};
			std::unique_ptr<RNG> default_rng = std::make_unique<DefaultRNG>();
			std::unique_ptr<Analyzer> analyzer = std::make_unique<Analyzer>(std::move(default_rng), configs);

			auto row = Row{AgentBreed::Breed_C, 132802001.0, 66, 3, 250, 25.3, 16.6, 5.1, false, 4};
			Assert::AreEqual(0, 1);
		}

	};
}
