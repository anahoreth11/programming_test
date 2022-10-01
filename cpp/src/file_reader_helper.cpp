#include "file_reader_helper.h"

#include <fstream>
#include <sstream>

std::string get_line_from_stream(std::istream& file_stream, char separator) {
    std::string line;
    std::getline(file_stream, line, separator);
    return line;
}

std::string get_str_value_from_csv_stream(std::istream& csv_stream) {
	std::string str_value;
	std::getline(csv_stream, str_value, ',');
	return str_value;
}
