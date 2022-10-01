#include "config_parser.h"

#include <fstream>
#include <sstream>

#include "file_reader_helper.h"


// const double DEFAULT_BRAND_FACTOR = 1.0;
std::string DEFAULT_INPUT_FILE_NAME = "input_data.csv";
std::string DEFAULT_OUTPUT_FILE_NAME = "output_data.txt";
bool DEFAULT_IS_FULL_DATA = false;;


std::optional<Configs> get_configs_from_line(const std::string& config_line) {
	std::istringstream configs_stream(config_line);
	std::string brand_factor_str = get_str_value_from_csv_stream(configs_stream);
	std::string input_file_name = get_str_value_from_csv_stream(configs_stream);
	std::string output_file_name = get_str_value_from_csv_stream(configs_stream);
	std::string is_full_data_str = get_str_value_from_csv_stream(configs_stream);
	if (brand_factor_str.empty() || input_file_name.empty()
		|| output_file_name.empty() || is_full_data_str.empty()) {
		return std::nullopt;
	}

	try {
		double brand_factor = std::stod(brand_factor_str);
		if (brand_factor < 0.1 || brand_factor > 2.9) {
			// TODO: log error
			return std::nullopt;
		}
		bool is_full_data = is_full_data_str != "0";
		return Configs{ brand_factor , input_file_name , output_file_name ,is_full_data };
	}
	catch (...) {
		// TODO: log error
		return std::nullopt;
	}
}

std::optional<Configs> get_configs_from_file(const std::string& config_file_name) {
	std::ifstream config_file_stream(config_file_name, std::ios::in);
	std::string configs_line = get_line_from_stream(config_file_stream);
	if (configs_line.empty()) {
		return std::nullopt;
	}
	return get_configs_from_line(configs_line);
}