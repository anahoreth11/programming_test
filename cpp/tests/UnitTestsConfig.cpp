#include "pch.h"
#include "CppUnitTest.h"

#include "../src/stream_reader_helper.cpp"
#include "../src/config_parser.h"
#include "../src/config_parser.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		TEST_METHOD(TestConfigParsingError)
		{
			std::string s = "12,3,4";
			auto config = get_configs_from_line(s);
			Assert::IsFalse(config.has_value());
		}
		TEST_METHOD(TestConfigParsingOK)
		{
			std::string s = "2.0,input.csv,output.txt,0";
			auto config = get_configs_from_line(s);
			Assert::IsTrue(config.has_value());
			Assert::AreEqual(config->brand_factor, 2.0, 0.0001);
			Assert::AreEqual(config->input_file_name, { "input.csv" });
			Assert::AreEqual(config->output_file_name, { "output.txt" });
			Assert::IsFalse(config->is_full_data);
		}
		TEST_METHOD(TestConfigParsingBadBrandFactor)
		{
			std::string s = "5.0,input.csv,output.txt,0";
			auto config = get_configs_from_line(s);
			Assert::IsFalse(config.has_value());
		}
		TEST_METHOD(TestConfigParsingEmptyValue)
		{
			std::string s = "5.0,input.csv,0";
			auto config = get_configs_from_line(s);
			Assert::IsFalse(config.has_value());
		}
	};
}
