#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/erdos_renyi_generator.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <iostream>
#include <fstream>
#include <string>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
typedef boost::sorted_erdos_renyi_iterator<boost::mt19937, Graph> ERGen;
typedef boost::graph_traits<Graph>::edge_iterator edge_iterator;
typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

extern "C" void Erdos_Renyi_randGen(int v, float p, char* outputFile);

void Erdos_Renyi_randGen(int v, float p, char* outputFile){
	
	std::ofstream fp;
	boost::mt19937 gen;
	Graph g(ERGen(gen,v,p),ERGen(),v);
	
	IndexMap index = boost::get(boost::vertex_index,g);
	edge_iterator  ei, ei_end;
	std::tie (ei, ei_end) = edges(g);
	
	fp.open(outputFile);
	
	while(ei != ei_end){
		fp << index[source(*ei,g)] + 1 << ' ' << index[target(*ei,g)] + 1 << " 1" << std::endl;
		++ei;
	}
	
	fp.close();
	return;
}