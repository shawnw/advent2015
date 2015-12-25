#include <iostream>
#include <cmath>

bool presents(unsigned house, unsigned total) {
	unsigned s = (house * 10) + 10;
	unsigned limit = std::sqrt(house);
	
	for (unsigned elf = 2; elf < limit; elf += 1) {
		unsigned div = house / elf;
		unsigned rem = house % elf;
		if (rem == 0) {
			s += (elf * 10) + (div * 10);
			if (s >= total)
				return true;
		}
	}
	if (limit * limit == house)
		s += limit * 10;
	
	return s >= total;
}

bool presents2(unsigned house, unsigned total) {
	unsigned s = house * 11;
	unsigned limit = std::sqrt(house);
	for (unsigned elf = 2; elf < limit; elf += 1) {
			int div = house / elf;
			int rem = house % elf;
			if (rem == 0) {
				if (div <= 50)
					s += elf * 11;
				else if (elf <= 50)
					s += div * 11;
				if (div > 50 && elf > 50)
					break;
				if (s >= total)
					return true;
			}
	}
	if (limit * limit == house)
		s += limit * 11;
	
	return s >= total;
}

int main(void) {
	unsigned magic = 34000000;
	unsigned n = 1;
	while (1) {
		if (presents(n, magic))
			break;
		n += 1;
	}
	std::cout << "Part 1: House " << n << " gets the loot.\n";

	n = 1;
	while (1) {
	if (presents2(n, magic))
		break;
		n += 1;
	}
	std::cout << "Part 2: House " << n << " gets the loot.\n";

	return 0;
}