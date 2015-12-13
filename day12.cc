#include <iostream>
#include <string>
#include "json.hpp"

using nlohmann::json;

int sum_json(json j) {
	if (j.is_number())
		return j.get<int>();
	else if (j.is_string())
		return 0;
	else if (j.is_array()) {
		int sum = 0;
		for (auto element : j)
			sum += sum_json(element);
		return sum;
	} else if (j.is_object()) {
		int sum = 0;
		for (auto it = j.begin(); it != j.end(); ++it) {
			if (it.value() == "red")
				return 0;
			else 
				sum += sum_json(it.value());
		}
		return sum;
	} else {
		// Unhandled type
		return 0;
	}
}

int main(void) {
	std::string line;
	int sum = 0;	
	json j;
	
	std::cin >> j;
	for (auto element : j)
		sum += sum_json(element);	
	
	std::cout << "Total sum: " << sum << '\n';
	return 0;
}
