#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using lights = std::vector<std::vector<bool>>;

// true if haystart starts with needle
bool starts_with(const std::string &haystack, const std::string &needle) {
	return haystack.compare(0, needle.length(), needle) == 0;
}

// Handles turn on and turn off
void set_lights(lights &grid, const std::string &command) {
	std::string turn, onoff, through;
	char comma1, comma2;
	int x1, y1, x2, y2;
	std::istringstream cmd{command};
				
	cmd >> turn >> onoff >> x1 >> comma1 >> y1 >> through >> x2 >> comma2 >> y2;
	bool v = onoff == "on";
	for (int x = x1; x <= x2; x += 1) {
		for (int y = y1; y <= y2; y += 1) {
			grid[x][y] = v;
		}
	}
}

// Handles toggle
void toggle_lights(lights &grid, const std::string &command) {
	std::string toggle, through;
	char comma1, comma2;
	int x1, y1, x2, y2;
	std::istringstream cmd{command};
				
	cmd >> toggle >> x1 >> comma1 >> y1 >> through >> x2 >> comma2 >> y2;
	for (int x = x1; x <= x2; x += 1) {
		for (int y = y1; y <= y2; y += 1) {
			grid[x][y] = !grid[x][y];
		}
	}
}

int main(void) {
	lights grid(1000, std::vector<bool>(1000, false));
	std::string command;
	
	while (std::getline(std::cin, command)) {
		if (starts_with(command, "turn on") ||
			starts_with(command, "turn off"))
			set_lights(grid, command);
		else if (starts_with(command, "toggle"))
			toggle_lights(grid, command);
		else
			std::cerr << "Unknown command: " << command << '\n';
	}
		
	int lit = 0;
	for (auto &row : grid) {
		for (auto light : row) { 
			if (light)
				lit += 1;
		}
	}
	std::cout << "Number of lit lights: " << lit << '\n';
	return 0;
}
