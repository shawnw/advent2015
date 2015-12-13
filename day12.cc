#include <iostream>
#include <string>
#include <regex>


int main(void) {
	std::string line;
	std::regex number{R"(-?\d+)"};
	int sum = 0;
	
	
	while (std::getline(std::cin, line)) {
		std::regex_token_iterator<std::string::iterator> rit{line.begin(), line.end(), number}, rend{};
		while (rit != rend)
			sum += std::stoi(*rit++);
	}
	
	std::cout << "Total sum: " << sum << '\n';
	return 0;
}
