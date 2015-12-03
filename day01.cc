#include <iostream>

int main(void) {
	int floor = 0;
	char p;
	
	while (std::cin >> p) {
		if (p == '(')
			floor += 1;
		else if (p == ')')
			floor -= 1;
	}
	std::cout << "Floor " << floor << '\n';
	return 0;
}