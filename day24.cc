#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <string>
#include <nmmintrin.h>

using ivec = std::vector<int>;
using std::uint64_t;

int weight(const ivec &presents) {
	return std::accumulate(presents.begin(), presents.end(), 0);
}

template<class T, class binary_op>
T foldit(ivec &v, unsigned c, T total, binary_op op) {
	for (unsigned n = 0; n < v.size(); n += 1)
		if (c & (1 << n))
			total = op(total, v[n]);
	return total;
}

int weight(ivec &presents, unsigned c) {
	return foldit<int>(presents, c, 0, std::plus<int>());
}

uint64_t qe(ivec &presents, unsigned c) {
	return foldit<uint64_t>(presents, c, 1, std::multiplies<uint64_t>());
}

int size(unsigned c) {
	return _mm_popcnt_u32(c);
}

bool partition(ivec &presents, uint64_t &qe_val, int ways) {
	int minbag = INT_MAX;
	int goal = weight(presents) / ways;
	
	for (unsigned c = 1; c < (1U << presents.size()); c += 1) {
		if (weight(presents, c) != goal)
			continue;
		int s = size(c);
		if (s < minbag) {
			minbag = s;
			qe_val = qe(presents, c);
		} else if (s == minbag) 
			qe_val = std::min(qe_val, qe(presents, c));
	}
	return minbag < INT_MAX;
}

int main(int argc, char **argv) {
	ivec presents;
	int n;
	uint64_t qe = INT_MAX;
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " NPARTITIONS\n";
		return 1;
	}
	while (std::cin >> n)
		presents.push_back(n);
	if (partition(presents, qe, std::stoi(argv[1])))
		std::cout << "QE " << qe << '\n';
	else
		std::cout << "No solution found!\n";
	return 0;
}
			
	
	
	
	
	
	
	