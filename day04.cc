#include <iostream>
#include <string>
#include "md5.h"

bool okay_hash(const std::string &hash) {
	const static std::string leading_zeros {"00000"};
	return hash.compare(0, 5, leading_zeros) == 0;
}

std::string make_secret_key(const std::string &seed, int n) {
	return seed + std::to_string(n);
}

int main(void) {
	std::string seed;
	int magic;
	
	std::getline(std::cin, seed);
	
	for (magic = 1; true; magic += 1) {
		const std::string key = make_secret_key(seed, magic);
		const std::string hashed_key = md5(key);
		if (okay_hash(hashed_key)) {
			std::cout << magic << '\n';
			break;
		}
	}
	return 0;
}
	