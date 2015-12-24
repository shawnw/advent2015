#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <map>
#include <numeric>
#include <functional>
#include <set>
#include <iterator>

using smap = std::map<std::string, std::string>;
using svec = std::vector<std::string>;

std::string atoms_to_str(const svec &atoms) {
		std::ostringstream s;
		std::copy(atoms.begin(), atoms.end(), std::ostream_iterator<std::string>(s));
		return s.str();
}

int reduce(const std::string &molecule, smap &trans, const svec &tokens, int steps = 0) {
	auto i = trans.find(molecule);
	if (i != trans.end() && i->second == "e")
		return steps;
	
	std::vector<int> paths;
	for (auto &t : tokens) {
		std::string::size_type from = std::string::npos, p;
		while ((p = molecule.rfind(t, from)) != std::string::npos) {
				std::string nm = molecule;
				nm.replace(p, t.length(), trans[t]);
				int s = reduce(nm, trans, tokens, steps + 1);
				if (s > 0)
					paths.push_back(s);
				if (p == 0)
					break;
				from = p - 1;
			}
	}
	if (paths.empty())
		return -1;
	else
		return *std::min_element(paths.begin(), paths.end());
}

int main(void) {
	std::multimap<std::string, std::string> transformations;
	std::string line, molecule;
	std::regex trans_re{ R"((\w+) => (\w+))" };
	std::regex atom { R"([A-Z][a-z]?)" };
	
	
	while (std::getline(std::cin, line)) {
		std::smatch fields;
		if (std::regex_match(line, fields, trans_re)) {
				transformations.insert(std::make_pair(fields[1], fields[2]));
		} else if (!line.empty()) {
			molecule = std::move(line);
			break;
		}
	}
	
	std::regex_iterator<std::string::iterator> ri(molecule.begin(),
		molecule.end(), atom), rend;
	
	svec atoms;
	while (ri != rend) 
		atoms.push_back((ri++)->str());
	
	std::set<std::string> molecules;
	
	for (auto &a : atoms) {
			std::string orig = a;
			auto r = transformations.equal_range(a);
			for (auto ti = r.first; ti != r.second; ++ti) {
				a = ti->second;
				molecules.insert(atoms_to_str(atoms));
			}
			a = orig;
	}
	
	std::cout << molecules.size() << " distinct molecules.\n";
	
	smap rtrans;
	svec rhs;
	for (auto &t : transformations) {
		rhs.push_back(t.second);
		rtrans.insert(std::make_pair(t.second, t.first));
	}
	std::sort(rhs.begin(), rhs.end(),
			[](auto &a, auto &b) { return a.length() > b.length(); });	
	
	int steps = reduce(molecule, rtrans, rhs);
	
	std::cout << steps << " steps to derive the molecule.\n";
	
	return 0;
}