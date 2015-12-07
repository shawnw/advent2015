#include <iostream>
#include <string>
#include <regex>

bool isnice_part1(const std::string &word) {
	static std::regex naughty_sequences {"ab|cd|pq|xy"};
	static std::regex three_vowels { "[aeiou].*[aeiou].*[aeiou]" };
	static std::regex duplicate_letter { "(.)\\1" };
	
	if (!std::regex_search(word, three_vowels))
		return false;
	if (!std::regex_search(word, duplicate_letter))
		return false;
	return !std::regex_search(word, naughty_sequences);
}

bool isnice_part2(const std::string &word) {
	static std::regex repeating_pair { "(..).*\\1" };
	static std::regex repeating_single { "(.).\\1" };
	
	if (!std::regex_search(word, repeating_pair)) 
		return false;
	return std::regex_search(word, repeating_single);
}

int main(void) {
	std::string word;
	int nice_part1 = 0;
	int nice_part2 = 0;
	
	while (std::getline(std::cin, word)) {
		if (isnice_part1(word))
			nice_part1 += 1;
		if (isnice_part2(word)) 
			nice_part2 += 1;
	}
	std::cout << "Part 1 nice count: " << nice_part1 << '\n';
	std::cout << "Part 2 nice count: " << nice_part2 << '\n';
	return 0;
}