#include <string>
#include <list>
#include <utility>
#include <map>
#include <climits>
#ifndef VERT_H
#define VERT_H

using namespace std;

class Vertex {
public:
  list<pair<int, int> > neighbors;
  string label;
  int distance;
  string color;
  Vertex* prev;
  
  Vertex():label(""),distance(INT_MAX),color("WHITE"),prev(0){}
  Vertex(string d):label(d), distance(INT_MAX),color("WHITE"),prev(0){}
  ~Vertex(){}
};
#endif