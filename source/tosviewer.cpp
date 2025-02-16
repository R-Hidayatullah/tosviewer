// tosviewer.cpp : Defines the entry point for the application.
//

#include "tosviewer.h"
#include "ipf_formats.h"

int main() {
	std::cout << "Hello World!\n";

	IPF_Root ipf;

	if (!ipf.open_file("pickque.ipf")) {
		std::cerr << "Error: Could not open file.\n";
		return 1;
	}

	if (!ipf.parse_footer()) {
		std::cerr << "Error: Failed to read IPF Footer.\n";
		return 1;
	}

	if (!ipf.parse_file_table()) {
		std::cerr << "Error: Failed to read file table.\n";
		return 1;
	}

	ipf.debug_print(3);

	std::vector<uint8_t> file_data = ipf.extract_file_to_memory(0);
	if (!file_data.empty()) {
		std::cout << "Extracted " << file_data.size() << " bytes into memory.\n";
	}
	print_hex_debug(file_data,16);
	ipf_decrypt(file_data);
	print_hex_debug(file_data,16);
	std::vector<uint8_t> uncompressed = decompress_data(file_data, ipf.file_table[0].file_size_uncompressed);
	print_hex_debug(uncompressed,16);

	return 0;
}