#include <iostream>
#include <string>

int logical_length(const std::string &s) {
	int len = 0;
	
	for (int i = 1; i < s.length() - 1; ) {
		if (s[i] == '\\') {
			i += 1;
			if (s[i] == 'x') {
				i += 3;
				len += 1;
			} else if (s[i] == '\\' || s[i] == '"') {
				i += 1;
				len += 1;
			}
		} else {
			i += 1;
			len += 1;
		}
	}
	return len;
}


int main(void) {
	std::string line;
	int total_chars = 0;
	int logical_chars = 0;
	
	while (std::getline(std::cin, line)) {
		int ll;
		ll = logical_length(line);
		total_chars += line.length();
		logical_chars += ll;
		//std::cout << "Logical length of '" << line << "' is " << ll << '\n';
	}
	std::cout << (total_chars - logical_chars) << '\n';
	return 0;
}