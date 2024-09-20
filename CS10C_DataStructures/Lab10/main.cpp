#include <iostream>
#include <sstream>
#include "Graph.h"

int main(){
	ifstream input("input2.txt");
	if (!input.is_open()){
		cout << "Error opening file." << endl;
		return 1;
	}

	Graph test(input);
	test.bfs();
	test.output_graph("out2.dot");

	return 0;
}