#pragma once

#include <string>
#include <vector>

struct Configs {
	double brand_factor;
	std::string input_file_name;
	std::string output_file_name;
	bool is_full_data;
};

enum class AgentBreed {
	Breed_C,
	Breed_NC
};

struct Row {
	AgentBreed agent_breed;
	double policy_id; 
	int age;
	int social_grade;
	int payment_at_purchase;
	double attribute_brand;
	double attribute_price;
	double attribute_promotions;
	bool is_auto_renew;
	int inertia_for_switch;
};

struct Results {
	std::vector<double> breed_c_ids;
	std::vector<double> breed_nc_ids;
	std::vector<double> breed_c_lost_ids;
	std::vector<double> breed_c_gained_ids;
	std::vector<double> breed_c_regained_ids;
};
