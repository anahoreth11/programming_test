#include <iostream>

#include "analyzer.h"
#include "config_parser.h"
#include "reader.h"
#include "result_saver.h"
#include "stream_reader_helper.h"

int main(int argc, char** argv) {

	// configs
	std::string config_file_name{ argv[1] };
	auto configs_opt = get_configs_from_file(config_file_name);
	if (!configs_opt.has_value()) {
		std::cout << "Error in parsing configs\n";
		return 0;
	}

	std::ifstream file_stream(configs_opt->input_file_name);
	// TODO we can use this header
	std::string header_line = get_str_value_from_stream(file_stream, 0x0D);
	// reader init
	std::unique_ptr<Reader> file_reader 
		= std::make_unique<StreamReader>(file_stream);

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
