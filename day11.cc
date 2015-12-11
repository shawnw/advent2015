#include <iostream>
#include <string>
#include <regex>

// This would be trivial with perl.

bool valid_password(const std::string &p) {
	static std::regex repeated_pairs{ R"(([a-z])\1.*(?!\1\1)([a-z])\2)" };
	if (!std::regex_search(p, repeated_pairs)) 
		return false;

	const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	for (size_t i = 0; i < 24; i++) {
		if (p.find(alphabet + i, 0, 3) != std::string::npos)
			return p.find_first_of("ilo") == std::string::npos;
	}
	
	return false;
}

// Modifies the password string in-place.
void incr_password(std::string &p) {
	std::size_t pos;
	if ((pos = p.find_first_of("ilo")) != std::string::npos) {
		p[pos] += 1;
		if (pos < (p.length() - 1))
			p.replace(pos + 1, std::string::npos, p.length() - pos - 1, 'a');
	} else {
		for (auto c = p.rbegin(); c != p.rend(); ++c) {
			switch (*c) {
				case 'z':
					*c = 'a';
					break;
				case 'h': case 'k': case 'n':
					*c += 2;
					return;
				default:
					*c += 1;
					return;
			}
		}
	}
}

std::string next_password(std::string p) {
	do {
		incr_password(p);
	} while (!valid_password(p));
	return p;
}

int main(void) {
	std::cout << "Valid password tests:\n";
	std::string test_passwords[] = {"hijklmmn", "abbceffg", "abbcegjk", "abcdffaa", "ghjaabcc", "cqjxxyzz"};
	std::cout.setf(std::ios_base::boolalpha);
	for (auto p : test_passwords)
		std::cout << p << ": " << valid_password(p) << '\n';
	
	std::cout << "\nIncremented password tests:\n";
	std::string test_next[] = {"abcdefgh", "ghijklmn" /* Add yours here */, "cqjxjnds"};
	for (auto p : test_next) {
		std::string np1 = next_password(p);
		std::string np2 = next_password(np1);
		std::cout << p << " -> " << np1 << " -> " << np2 << '\n';
	}
	return 0;
}