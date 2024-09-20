#include <vector>
#include <fstream>
#include "Vertex.h"

#ifndef GRAPH_H
#define GRAPH_H

class Graph {
	private:
		vector<Vertex> vertices;

	public:
		Graph(ifstream &ifs);
		void output_graph(const string &fileName);
		void bfs();
};

#endif