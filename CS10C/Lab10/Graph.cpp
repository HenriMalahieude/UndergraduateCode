#include "Graph.h"
#include "Vertex.h"
#include <sstream>
#include <iostream>
#include <queue>

Graph::Graph(ifstream &ifs){
	int NodeCount, EdgeCount;
	ifs >> NodeCount >> EdgeCount; //Get Starter Data

	//Load Nodes
	for (int i = 0; i < NodeCount; i++){
		string temp;
		ifs >> temp;

		vertices.push_back(Vertex(temp));
	} //NOTE: The first input node is the start node for BFS

	//Load Edges
	for (int i = 0; i <= EdgeCount; i++){
		string temp;
		getline(ifs, temp);

		if (temp == ""){continue;}

		int fComma = temp.find(' ');
		string sourceLabel = temp.substr(0, fComma);
		//cout << temp << endl;

		temp = temp.substr(fComma+1);
		fComma = temp.find(' ');
		string sinkLabel = temp.substr(0, fComma);
		//cout << temp << endl;

		temp = temp.substr(fComma+1);
		stringstream converter(temp);

		int eDist;
		converter >> eDist;
		
		//cout << sourceLabel << " - " << eDist << " > " << sinkLabel << endl;

		for (unsigned k = 0; k < vertices.size(); k++){
			Vertex *tempV1 = &vertices.at(k);
			if (tempV1->label == sourceLabel){
				for (unsigned j = 0; j < vertices.size(); j++){
					Vertex *tempV2 = &vertices.at(j);
					if (tempV2 != tempV1 && tempV2->label == sinkLabel){
						tempV1->neighbors.push_back(make_pair(j, eDist));
						break;
					}
				}
				break;
			}
		}
	}
}

void Graph::output_graph(const string &fileName){
	ofstream outFS(fileName);
	if (!outFS.is_open()){
		cout << "Error" << endl;
		return;
	}

	outFS<<"digraph G {\n"<<endl;
    for(unsigned i = 0; i < vertices.size(); i++){ // for vertex
		outFS << vertices.at(i).label << " [label=\"" << vertices.at(i).label << " / " << vertices.at(i).distance << "\"]" << endl;
	}

	outFS << "\n";

	list<pair<int,int>>::iterator it; // for edges
	for(unsigned i = 0; i < vertices.size(); i++){ 
		it = vertices.at(i).neighbors.begin();

		while(it != vertices.at(i).neighbors.end()){
			outFS << vertices.at(i).label << " -> " << vertices.at(it->first).label << " [ label = \"" << it->second << "\"]" << endl;
			it++;
		}
	}
	//Figure out how to output

    outFS<<"\n}";
	outFS.close();
	string jpgFilename = fileName.substr(0,fileName.size()-4)+".jpg";
    string command = "dot -Tjpg " + fileName + " -o " + jpgFilename;
    system(command.c_str());
}

void Graph::bfs(){
	queue<Vertex*> q;
	Vertex *u;
	list<pair<int,int>>::iterator it;

	for(unsigned i = 0; i < vertices.size(); i++){
		vertices.at(i).color = "WHITE";
		vertices.at(i).distance = INT_MAX;
		vertices.at(i).prev = 0;
	}

	vertices.at(0).color = "GRAY";
	vertices.at(0).distance = 0;
	vertices.at(0).prev = 0;

	q.push(&vertices.at(0));
	while(!q.empty()){
		//cout << q.size() << " ";
		u = q.front();
		q.pop();

		//cout << u->label << " " << u->neighbors.size() << ": ";

		if (u->neighbors.size() > 0){
			it = u->neighbors.begin();

			while(it != u->neighbors.end()){
				Vertex *temp =  &vertices.at(it->first);
				//cout << temp->label << " " << temp->color << ", ";

				if(vertices.at(it->first).color == "WHITE"){					
					temp->color = "GRAY";
					temp->distance = u->distance + it->second;
					temp->prev = u;
					q.push(temp);
				}
				it++;
			}

			//cout << endl;
		}

		/*
		for(unsigned i = 0; i < vertices.size(); i++){
			if(u->label == vertices.at(i).label){
				break;
			}
			vertices.at(i).color = "BLACK";
		}*/
	}
}