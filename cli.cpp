#include <iostream>
#include "prompt.hpp"

int main(int argc, char** argv) {
	std::string buffer;
	while (true) {
		std::cout << "> ";
		std::cin >> buffer;
		auto command = PomprtCommandPraser::parse(buffer);

	}

	return 0;
}