#include "reader.h"
#include "stream_reader_helper.h"

#include <sstream>

std::optional<Row> StreamReader::ReadRow() {
	std::string line = get_str_value_from_stream(_stream, 0x0D);
	std::istringstream line_stream(line);
	std::string agent_breed_str = get_str_value_from_stream(line_stream, ',');
	std::string policy_id_str = get_str_value_from_stream(line_stream, ',');
	std::string age_str = get_str_value_from_stream(line_stream, ',');
	std::string social_grade_str = get_str_value_from_stream(line_stream, ',');
	std::string payment_at_purchase_str = get_str_value_from_stream(line_stream, ',');
	std::string attribute_brand_str = get_str_value_from_stream(line_stream, ',');
	std::string attribute_price_str = get_str_value_from_stream(line_stream, ',');
	std::string attribute_promotions_str = get_str_value_from_stream(line_stream, ',');
	std::string is_auto_renew_str = get_str_value_from_stream(line_stream, ',');
	std::string inertia_for_switch_str = get_str_value_from_stream(line_stream, ',');
	if (agent_breed_str.empty() || policy_id_str.empty()
		|| age_str.empty() || social_grade_str.empty()
		|| payment_at_purchase_str.empty() || attribute_brand_str.empty()
		|| attribute_price_str.empty() || attribute_promotions_str.empty()
		|| is_auto_renew_str.empty() || inertia_for_switch_str.empty()) {
		return std::nullopt;
	}

	try {
		AgentBreed agent_breed = agent_breed_str == "Breed_C"
			? AgentBreed::Breed_C : AgentBreed::Breed_NC;

		double policy_id = std::stod(policy_id_str);
		int age = std::stoi(age_str);
		int social_grade = std::stoi(social_grade_str);
		int payment_at_purchase = std::stoi(payment_at_purchase_str);
		double attribute_brand = std::stod(attribute_brand_str);
		double attribute_price = std::stod(attribute_price_str);
		double attribute_promotions = std::stod(attribute_promotions_str);
		bool is_auto_renew = is_auto_renew_str == "1" ? true : false;
		int inertia_for_switch = std::stoi(inertia_for_switch_str);

		return Row{ agent_breed, policy_id, age, social_grade, payment_at_purchase,
			attribute_brand, attribute_price, attribute_promotions, 
			is_auto_renew, inertia_for_switch };
	}
	catch (...) {
		// TODO: log error
		return std::nullopt;
	}

	return std::nullopt;
}
