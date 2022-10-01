#include "pch.h"
#include "CppUnitTest.h"

#include <string>

#include "../src/reader.h"
#include "../src/reader.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		TEST_METHOD(TestDataEmpty)
		{
			std::string s = "12,3,4";
			std::istringstream string_stream(s);
			StreamReader reader(string_stream);
			auto row = reader.ReadRow();
			Assert::IsFalse(row.has_value());
		}

		TEST_METHOD(TestDataOneLineOK)
		{
			std::string s = "Breed_C,132802001.0,66,3,250,25.3,16.6,5.1,0,4";
			std::istringstream string_stream(s);
			StreamReader reader(string_stream);
			auto row = reader.ReadRow();
			Assert::IsTrue(row.has_value());
			Assert::IsTrue(row->agent_breed == AgentBreed::Breed_C);
			Assert::AreEqual(row->policy_id, 132802001.0, 0.0001);
			Assert::AreEqual(row->age, 66);
			Assert::AreEqual(row->social_grade, 3);
			Assert::AreEqual(row->payment_at_purchase, 250);
			Assert::AreEqual(row->attribute_brand, 25.3, 0.0001);
			Assert::AreEqual(row->attribute_price, 16.6, 0.0001);
			Assert::AreEqual(row->attribute_promotions, 5.1, 0.0001);
			Assert::IsFalse(row->is_auto_renew);
			Assert::AreEqual(row->inertia_for_switch, 4);
			row = reader.ReadRow();
			Assert::IsFalse(row.has_value());
		}
		TEST_METHOD(TestDataTwoLinesOK)
		{
			std::string s = "Breed_C,132802001.0,66,3,250,25.3,16.6,5.1,0,4\rBreed_NC,132802002.0,67,4,251,26.3,17.6,6.1,1,5";
			std::istringstream string_stream(s);
			StreamReader reader(string_stream);
			auto row = reader.ReadRow();
			Assert::IsTrue(row.has_value());
			Assert::IsTrue(row->agent_breed == AgentBreed::Breed_C);
			Assert::AreEqual(row->policy_id, 132802001.0, 0.0001);
			Assert::AreEqual(row->age, 66);
			Assert::AreEqual(row->social_grade, 3);
			Assert::AreEqual(row->payment_at_purchase, 250);
			Assert::AreEqual(row->attribute_brand, 25.3, 0.0001);
			Assert::AreEqual(row->attribute_price, 16.6, 0.0001);
			Assert::AreEqual(row->attribute_promotions, 5.1, 0.0001);
			Assert::IsFalse(row->is_auto_renew);
			Assert::AreEqual(row->inertia_for_switch, 4);
			row = reader.ReadRow();
			Assert::IsTrue(row.has_value());
			Assert::IsTrue(row->agent_breed == AgentBreed::Breed_NC);
			Assert::AreEqual(row->policy_id, 132802002.0, 0.0001);
			Assert::AreEqual(row->age, 67);
			Assert::AreEqual(row->social_grade, 4);
			Assert::AreEqual(row->payment_at_purchase, 251);
			Assert::AreEqual(row->attribute_brand, 26.3, 0.0001);
			Assert::AreEqual(row->attribute_price, 17.6, 0.0001);
			Assert::AreEqual(row->attribute_promotions, 6.1, 0.0001);
			Assert::IsTrue(row->is_auto_renew);
			Assert::AreEqual(row->inertia_for_switch, 5);
		}
	};
}
