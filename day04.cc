// Takes one argument, the length of the leading 0s needed in the md5 hash.

#include <iostream>
#include <string>
#include "md5.h"

class compare_hash {
	private:
		std::string prefix;
	public:
		explicit compare_hash(int n) : prefix(n, '0') {}
		bool matches(const std::string hash) {
			return hash.compare(0, prefix.length(), prefix) == 0;
		}
};

std::string make_secret_key(const std::string &seed, int n) {
	return seed + std::to_string(n);
}

int main(int argc, char ** argv) {
	std::string seed;
	int magic;
	
	if (argc != 2) {
		std::cerr << "Missing prefix length argument.\n";
		return 1;
	}
	
	compare_hash test(std::stoi(argv[1]));
	
	std::getline(std::cin, seed);
	
	for (magic = 1; true; magic += 1) {
		const std::string key = make_secret_key(seed, magic);
		const std::string hashed_key = md5(key);
		if (test.matches(hashed_key)) {
			std::cout << '\n' << magic << '\n';
			break;
		} else if (magic % 10000 == 0)
			std::cout << '.';
	}
	return 0;
}
	