#include "Node.h"
using namespace std;


Node::Node(string d){
    data = d;
    right = nullptr;
    left = nullptr;
    height = 0;
}

string Node::getdata(){
    return data;
}

int Node::getHeight(){
    return height;
}

void Node::setHeight(int h){
    height = h;
}

void Node::setleft(Node* left){
    this->left = left;
}

Node* Node::getleft(){
    return left;
}

void Node::setright(Node* right){
    this->right = right;
}

Node* Node::getright(){
    return right;
}