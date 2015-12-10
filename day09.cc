#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <algorithm>
#include <climits>
#include <iterator>

using conn = std::map<std::pair<std::string, std::string>, int>;

struct no_such_route {};

int route_length(conn &connections, const std::vector<std::string> &cities, std::string current) {
	int distance = 0;
	for (const auto &city : cities) {
		auto route = std::make_pair(current ,city);
		if (connections.find(route) == connections.end()) 
			throw no_such_route();
		distance += connections[route];
		current = city;
	}
	return distance;
}

int main(void) {
	std::string line;
	std::regex edge_re { "(\\w+) to (\\w+) = (\\d+)" };
	std::set<std::string> cities;
	conn connections;
	int min_distance = INT_MAX;
	int max_distance = 0;
	
	while (std::getline(std::cin, line)) {
		std::smatch fields;
		if (std::regex_match(line, fields, edge_re)) {
			cities.insert(fields[1]);
			cities.insert(fields[2]);
			int d = stoi(fields[3]);
			connections.emplace(std::make_pair(fields[1], fields[2]), d);
			connections.emplace(std::make_pair(fields[2], fields[1]), d);
		} else {
			std::cerr << "Unknown line '" << line << "'\n";
		}	
	}
	
	for (const auto city : cities) {
		std::vector<std::string> remaining{cities.begin(), cities.end()};
		remaining.erase(std::lower_bound(remaining.begin(), remaining.end(), city));
		do {
			try {
				int d = route_length(connections, remaining, city);
				min_distance = std::min(min_distance, d);
				max_distance = std::max(max_distance, d);
				//std::cout << city << " -> ";
				//std::copy(remaining.begin(), remaining.end(), std::ostream_iterator<std::string>(std::cout, " -> "));
				//std::cout << " = " << d << '\n';
			} catch (no_such_route e) {
			}
		} while (std::next_permutation(remaining.begin(), remaining.end()));			
	}
	
	std::cout << "Minimum distance: " << min_distance << '\n';
	std::cout << "Maximum distance: " << max_distance << '\n';
	
	return 0;
}