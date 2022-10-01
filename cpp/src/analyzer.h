#pragma once

#include "file_reader.h"
#include "data_types.h"
#include "RNG.h"

class Analyzer {
public:
	Analyzer(std::unique_ptr<RNG>&& rng, const Configs& configs);
	void Analyze(const Row& row);
	std::vector<Results> GetResults();

	double GetAffinity(const Row& row);
	bool IsCConditionTrue(const Row& row);
	bool IsNCConditionTrue(const Row& row);
private:
	int _ages_count;
	std::unique_ptr<RNG> _rng;
	Configs _configs;
	std::vector<Results> _results;
};

