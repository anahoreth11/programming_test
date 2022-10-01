#include "result_saver.h"

#include <fstream>

void write_vector_to_stream(std::ostream& stream, 
		const std::vector<double>& values) {
	for (int i = 0; i < values.size(); ++i) {
		stream << std::fixed << values[i];
		if (i < values.size() - 1) {
			stream << ",";
		}
	}
	stream << "\n";
}

void save_results(const std::vector<Results>& results, 
		const std::string& output_file_name) {
	std::ofstream output_stream(output_file_name);
	output_stream.precision(1);
	for (int age = 0; age < results.size(); ++age) {
		write_vector_to_stream(output_stream, results[age].breed_c_ids);
		write_vector_to_stream(output_stream, results[age].breed_nc_ids);
		write_vector_to_stream(output_stream, results[age].breed_c_lost_ids);
		write_vector_to_stream(output_stream, results[age].breed_c_gained_ids);
		write_vector_to_stream(output_stream, results[age].breed_c_regained_ids);
	}
}
