#include <iostream>
#include <string>
#include <regex>

bool isnice(const std::string &word) {
	static std::regex naughty_sequences {"ab|cd|pq|xy"};
	static std::regex three_vowels { "[aeiou].*[aeiou].*[aeiou]" };
	static std::regex duplicate_letter { "(.)\\1" };
	
	if (!std::regex_search(word, three_vowels))
		return false;
	
	if (!std::regex_search(word, duplicate_letter))
		return false;

	return !std::regex_search(word, naughty_sequences);
}

int main(void) {
	std::string word;
	int nice = 0;
	
	while (std::getline(std::cin, word)) {
		if (isnice(word)) {
			//std::cout << "'" << word << "' is nice.\n";
			nice += 1;
		} else {
			//std::cout << "'" << word << "' is naughty!\n";
		}
	}
	std::cout << nice << '\n';
	return 0;
}