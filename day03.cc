#include <iostream>
#include <map>
#include <utility>

using point = std::pair<int, int>;

int main(void) {
	int x = 0, y = 0;
	std::map<point, int> grid;
	char dir;
	
	grid[std::make_pair(0,0)] = 1;
	while (std::cin >> dir) {
		switch (dir) {
			case '^':
				x += 1;
				break;
			case '>':
				y += 1;
				break;
			case '<':
				y -= 1;
				break;
			case 'V':
			case 'v':
				x -= 1;
				break;
			default:
				std::cerr << "Invalid character '" << dir << "'\n";
				continue;
		}
		grid[std::make_pair(x, y)] += 1;		
	}
	
	std::cout << "Number of houses: " << grid.size() << '\n';
	return 0;
}