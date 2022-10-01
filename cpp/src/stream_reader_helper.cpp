#include "stream_reader_helper.h"

#include <fstream>
#include <sstream>

std::string get_str_value_from_stream(std::istream& file_stream, char separator) {
    std::string line;
    std::getline(file_stream, line, separator);
    return line;
}
