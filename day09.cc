#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

using namespace boost;

using edge = std::pair<std::string, std::string>
using graph = adjancency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int>>;
using vertex_descriptor = graph_traits<graph>::vertex_descriptor;

int main(void) {
	std::string line;
	std::vector<edge> edge_array;
	std::vector<int> distances;
	std::regex edge_re { R"(\w+) to (\w+) = (\d+)" };
	
	while (std::getline(std::cin, line)) {
		std::smatch fields;
		if (std::regex_match(line, fields, edge_re) {
			edge_array.emplace_back(fields[1], fields[2]);
			distances.push_back(fields[3]);
		} else {
			std::cerr << "Unknown line '" << line << "'\n";
		}	
	}
	
	graph g(edge_array.begin(), edge_array.end(), weights, edge_array.length());
	property_map<graph, edge_weight_t>::type weighttype = get(edge_weight, t);
	std::vector<vertex_descriptor> p(num_vertices(g));
	std::vector<int> d(num_vertices(g));
	vertex_descriptor s = vertex(,g);
	
	dijkstra_shortest_paths(g, s,
                          predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))).
                          distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));

	std::cout << "distances and parents:" << std::endl;
	graph_traits < graph_t >::vertex_iterator vi, vend;
	for (std::tie(vi, vend) = vertices(g); vi != vend; ++vi) {
		std::cout << "distance(" << name[*vi] << ") = " << d[*vi] << ", ";
		std::cout << "parent(" << name[*vi] << ") = " << name[p[*vi]] << std::endl;
	}
	std::cout << std::endl;
	return 0;
}