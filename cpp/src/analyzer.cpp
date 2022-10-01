#include "analyzer.h"

Analyzer::Analyzer(std::unique_ptr<RNG>&& rng, const Configs& configs): 
	_rng(std::move(rng)), _configs(configs), _ages_count(15), 
	_results(std::vector<Results>(_ages_count, Results{})) {}


double Analyzer::GetAffinity(const Row& row) {
	double rand = _rng->get_random();
	return row.payment_at_purchase / row.attribute_price + rand * row.attribute_promotions * row.inertia_for_switch;
}

bool Analyzer::IsCConditionTrue(const Row& row) {
	double affinity = GetAffinity(row);
	return affinity < row.social_grade * row.attribute_brand;
}

bool Analyzer::IsNCConditionTrue(const Row& row) {
	double affinity = GetAffinity(row);
	return affinity < row.social_grade * row.attribute_brand * _configs.brand_factor;
}

void Analyzer::Analyze(const Row& row) {
	AgentBreed current_breed = row.agent_breed;
	bool has_lost = false;
	for (int age = 0; age < _ages_count; ++age) {
		if (row.is_auto_renew) {
			if (current_breed == AgentBreed::Breed_C) {
				_results[age].breed_c_ids.push_back(row.policy_id);
			} else {
				_results[age].breed_nc_ids.push_back(row.policy_id);
			}
			continue;
		}
		if (current_breed == AgentBreed::Breed_C) {
			if (IsCConditionTrue(row)) {
				current_breed = AgentBreed::Breed_NC;
				_results[age].breed_nc_ids.push_back(row.policy_id);
				has_lost = true;
				if (row.agent_breed == AgentBreed::Breed_C) {
					_results[age].breed_c_lost_ids.push_back(row.policy_id);
				}
			}
			else {
				_results[age].breed_c_ids.push_back(row.policy_id);
			}
		} else {
			if (IsNCConditionTrue(row)) {
				current_breed = AgentBreed::Breed_C;
				_results[age].breed_c_ids.push_back(row.policy_id);
				if (row.agent_breed == AgentBreed::Breed_NC) {
					_results[age].breed_c_gained_ids.push_back(row.policy_id);
				}
				if (has_lost) {
					_results[age].breed_c_regained_ids.push_back(row.policy_id);
				}
			}
			else {
				_results[age].breed_nc_ids.push_back(row.policy_id);
			}
		}
	}
}

std::vector<Results> Analyzer::GetResults() {
	if (_configs.is_full_data) {
		return _results;
	}
	return { _results[_ages_count - 1]};
}

