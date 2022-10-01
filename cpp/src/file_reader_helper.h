#pragma once

#include <istream>

std::string get_line_from_stream(std::istream& config_file_stream, char separator = 0x0A);

std::string get_str_value_from_csv_stream(std::istream& configs_stream);
