#include <iostream>
#include <algorithm>
#include <array>

int compute(int l, int w, int h) {
	int surface_area = 2*l*w + 2*w*h + 2*h*l;
	
	std::array<int,3> sides = {l, w, h};
	std::sort(sides.begin(), sides.end());
	
	return surface_area + sides[0]*sides[1];
}

int main(void) {
	int l, w, h;
	char x1, x2;
	long total_paper = 0;
	
	while (std::cin >> l >> x1 >> w >> x2 >> h) 
		total_paper += compute(l, w, h);
	
	std::cout << "Square feet: " << total_paper;
	
	return 0;
}