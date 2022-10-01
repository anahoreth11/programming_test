


#include <iostream>


#include "analyzer.h"
#include "file_reader.h"
#include "config_parser.h"
#include "file_reader_helper.h"

void save_results(const std::vector<Results>& results, const std::string & output_file_name) {
	std::ofstream output_stream(output_file_name);
	output_stream.precision(1);
	for (int age = 0; age < results.size(); ++age) {
		if (results[age].breed_c_ids.size() > 0) {
			for (int i = 0; i < results[age].breed_c_ids.size(); ++i) {
				output_stream << std::fixed <<results[age].breed_c_ids[i];
				if (i < results[age].breed_c_ids.size() - 1) {
					output_stream << ",";
				}
			}
			output_stream << "\n";
		}
		if (results[age].breed_nc_ids.size() > 0) {
			for (int i = 0; i < results[age].breed_nc_ids.size(); ++i) {
				output_stream << results[age].breed_nc_ids[i];
				if (i < results[age].breed_nc_ids.size() - 1) {
					output_stream << ",";
				}
			}
			output_stream << "\n";
		}
		if (results[age].breed_c_lost_ids.size() > 0) {
			for (int i = 0; i < results[age].breed_c_lost_ids.size(); ++i) {
				output_stream << results[age].breed_c_lost_ids[i];
				if (i < results[age].breed_c_lost_ids.size() - 1) {
					output_stream << ",";
				}
			}
			output_stream << "\n";
		}
		if (results[age].breed_c_gained_ids.size() > 0) {
			for (int i = 0; i < results[age].breed_c_gained_ids.size(); ++i) {
				output_stream << results[age].breed_c_gained_ids[i];
				if (i < results[age].breed_c_gained_ids.size() - 1) {
					output_stream << ",";
				}
			}
			output_stream << "\n";
		}
		if (results[age].breed_c_regained_ids.size() > 0) {
			for (int i = 0; i < results[age].breed_c_regained_ids.size(); ++i) {
				output_stream << results[age].breed_c_regained_ids[i];
				if (i < results[age].breed_c_regained_ids.size() - 1) {
					output_stream << ",";
				}
			}
			output_stream << "\n";
		}
		
	}
}

int main(int argc, char** argv) {

	// configs
	std::string config_file_name{argv[1]};
	auto configs_opt = get_configs_from_file(config_file_name);
	if (!configs_opt.has_value()) {
		std::cout << "Error in parsing configs\n";
		return 0;
	}

	std::ifstream file_stream(configs_opt->input_file_name);
	// TODO we can use this header
	std::string header_line = get_line_from_stream(file_stream, 0x0D);
	// reader init
	std::unique_ptr<Reader> file_reader = std::make_unique<StreamReader>(file_stream);

	// analyze
	std::unique_ptr<RNG> rng = std::make_unique<MT_RNG>();
	std::unique_ptr<Analyzer> analyzer 
		= std::make_unique<Analyzer>(std::move(rng), configs_opt.value());
	
	auto row = file_reader->ReadRow();
	while (row != std::nullopt) {
		analyzer->Analyze(row.value());
		row = file_reader->ReadRow();
	}

	// output
	auto results = analyzer->GetResults();
	save_results(results, configs_opt->output_file_name);

	return 0;
}