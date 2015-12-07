#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <algorithm>
#include <cctype>

enum OPS {
	OP_ERR, OP_AND, OP_OR, OP_NOT, OP_LSHIFT, OP_RSHIFT, OP_STORE 
};

using stype = unsigned short;

struct gate {
	OPS op;
	std::string lhs;
	std::string rhs;
	bool memoized;
	stype val;
};

using logic = std::map<std::string, gate>;

bool isnumber(const std::string &n) {
	return std::all_of(n.begin(), n.end(), ::isdigit);
}

OPS stoop(const std::string s) {
	if (s == "AND")
		return OP_AND;
	else if (s == "OR")
		return OP_OR;
	else if (s == "LSHIFT")
		return OP_LSHIFT;
	else if (s == "RSHIFT")
		return OP_RSHIFT;
	else
		return OP_ERR;
}

stype solve_for(logic &, const std::string &);

stype solve_wire(logic &circuit, const std::string &num_or_wire) {
	if (isnumber(num_or_wire))
		return std::stoi(num_or_wire);
	else
		return solve_for(circuit, num_or_wire);
}

stype solve_for(logic &circuit, const std::string &wire) {
	
	if (circuit.find(wire) == circuit.end()) {
		std::cerr << "Unknown wire '" << wire << "'\n";
		return 0;
	}
	
	gate &g = circuit[wire];
	if (g.memoized) {
		return g.val;
	} else {
		stype r;
		switch (g.op) {
			case OP_STORE:
				r = solve_wire(circuit, g.lhs);
				break;
			case OP_AND:
				r = solve_wire(circuit, g.lhs) & solve_wire(circuit, g.rhs);
				break;
			case OP_OR:
				r = solve_wire(circuit, g.lhs) | solve_wire(circuit, g.rhs);
				break;
			case OP_LSHIFT:
				r = solve_wire(circuit, g.lhs) << solve_wire(circuit, g.rhs);
				break;
			case OP_RSHIFT:
				r = solve_wire(circuit, g.lhs) >> solve_wire(circuit, g.rhs);
				break;
			case OP_NOT:
				r = ~solve_wire(circuit, g.lhs);
				break;
		}
		g.memoized = true;
		g.val = r;
		return r;
	}
}

void reset_logic(logic &circuit) {
	for (auto &gate : circuit)
		gate.second.memoized = false;
}

int main(void) {
	std::string command;
	logic circuit;
    std::regex assign_op{ "(\\w+) -> (\\w+)" };
	std::regex not_op{ "NOT (\\w+) -> (\\w+)" };
	std::regex binary_op{ "(\\w+) (AND|OR|LSHIFT|RSHIFT) (\\w+) -> (\\w+)" };
	
	while (std::getline(std::cin, command)) {
		std::smatch fields;
		gate g;
		g.memoized = false;
		g.val = 0;
		if (std::regex_match(command, fields, assign_op)) {
			g.op = OP_STORE;
			g.lhs = fields[1];
			g.rhs = "";
			circuit[fields[2]] = g;
		} else if (std::regex_match(command, fields, not_op)) {
			g.op = OP_NOT;
			g.lhs = fields[1];
			g.rhs = "";
			circuit[fields[2]] = g;
		} else if (std::regex_match(command, fields, binary_op)) {
			g.op = stoop(fields[2]);
			g.lhs = fields[1];
			g.rhs = fields[3];
			circuit[fields[4]] = g;
		} else {
			std::cerr << "Unknown gate: " << command << '\n';
		}
	}
	
	std::cout << "There are a total of " << circuit.size() << " gates.\n";
	
	for (auto &wires : circuit)
		std::cout << wires.first << ": " << solve_for(circuit, wires.first) << '\n';
	
	stype a = solve_for(circuit, "a");
	std::cout << "Initial value of a: " << a << '\n';
	
	reset_logic(circuit);
	gate b;
	b.op = OP_STORE;
	b.memoized = true;
	b.val = a;
	circuit["b"] = b;
	
	a = solve_for(circuit, "a");
	std::cout << "New value of a: " << a;
	
	return 0;
}
	